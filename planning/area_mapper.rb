require 'yaml'
require 'active_support/all'
require 'colorize'

module Array2D
  def self.new(x, y, fill)
    Array.new(x) { Array.new(y) { fill } }    
  end
end

class Area
  RAW = YAML.load(File.read(File.join(File.dirname(__FILE__), './areas.yml')))
  LIST = {}

  COLORS = {
    town: { color: :white, background: :light_red },
    city: { color: :black, background: :yellow },
    waypoint: :light_cyan,
    cave: :magenta,
    trial: :cyan,
    forest: :green,
  }

  class << self
    def get(name)
      LIST[name] || begin
        raise "#{name} is not an area" unless RAW[name]
        new(name, RAW[name])
      end
    end
  end

  attr_reader :name
  alias to_s name
  alias inspect name

  attr_writer :rendered

  def initialize(name, data)
    @name = name
    @data = data.with_indifferent_access

    LIST[name] = self
  end

  def about
    @data[:about]
  end

  def province
    @data[:province]
  end

  def type
    @data[:type].to_sym
  end

  def connections
    @connections ||= Connections.new(@data[:connections], self)
  end

  def icon
    if type == :route
      sign = connections.sign
      case
      when sign.ns?
        '┃'
      when sign.ew?
        '━'
      when sign.se?
        '┏'
      when sign.sw?
        '┓'
      when sign.ne?
        '┗'
      when sign.ne?
        '┛'
      when sign.nse?
        '┣'
      when sign.nsw?
        '┫'
      when sign.sew?
        '┳'
      when sign.new?
        '┻'
      when sign.nsew?
        '╋'
      else
        '.'
      end
    else
      Legend.number(type, self).colorize(COLORS[type])
    end
  end
  alias render icon

  def rendered?
    @rendered
  end

  def ==(other)
    return name == other.name if other.is_a?(Area)
    false
  end

  class Legend
    STORE = {}

    class << self
      def number(type, area)
        STORE[type] ||= []
        STORE[type] << area
        STORE[type].length.to_s
      end

      def inspect
        <<~HEREDOC
          
        -- LEGEND --
        
        #{STORE.map { |type, list| new(type, list).inspect }.join("\n")}
        HEREDOC
      end
      alias to_s inspect
    end

    attr_reader :type, :list

    def initialize(type, list)
      @type = type
      @list = list
    end

    def name
      type.to_s.pluralize.titlecase
    end

    def inspect
      color = Area::COLORS[type]

      <<~LEGEND
        #{name.colorize(color)}
        #{list.each_with_index.map { |item, i| "#{(i + 1).to_s.colorize(color)} #{item}" }.join("\t")}
      LEGEND
    end
    alias to_s inspect
  end

  class Connections
    include Enumerable

    def initialize(list, from)
      @list = list
      @from = from
    end

    %i|north south east west|.each do |dir|
      define_method dir do
        Area.get(@list[dir]) if @list[dir]
      end
    end

    def sign
      @sign ||= Sign.new(self)
    end

    def to_h
      h = {}

      %i|north south east west|.each { |dir|
        h[dir] = send(dir) if send(dir)
      }

      h
    end

    delegate :inspect, :keys, to: :to_h

    def each
      to_h.each do |dir, area|
        next unless area
        yield dir, area
      end
    end

    def each_for_render(base_pos)
      each do |dir, area|
        next if area.rendered?
        yield area, offset_from(dir, area, base_pos)
      end
    end

    private

    def offset_from(dir, area, base_pos)
      pos = base_pos.dup

      case dir
      when :north
        pos[1] -= 1
      when :south
        pos[1] += 1
      when :east
        pos[0] += 1
      when :west
        pos[0] -= 1
      end

      pos
    end

    class Sign
      def initialize(connections)
        @symbol = represent_as_symbol(connections)
      end
      
      def ==(other)
        @symbol == represent_as_symbol(other)
      end

      def method_missing(name, *a, &b)
        name = name.to_s

        if a.present? || b.present? || name[-1] != '?'
          return super
        end

        self == name[0..-2]
      end

      private

      def represent_as_symbol(input)
        case input
        when Area::Connections, Hash
          represent_as_symbol(input.keys)
        when Array
          input.map { |k| k.to_s[0] }.sort.join('').to_sym
        when String
          input.split('').sort.join('').to_sym
        when Symbol
          represent_as_symbol(input.to_s)
        end
      end
    end
  end
end

class Map
  SIZE = [25, 25]
  EMPTY_SQUARE = ' '

  def initialize
    @array = Array2D.new(*SIZE, EMPTY_SQUARE)
    populate_areas!
    clear_empty_rows!
  end

  def to_s
    @array.map { |row| row.join('') }.join("\n")
  end
  alias inspect to_s

  private

  def populate_areas!
    populate_area(STARTING_AREA, STARTING_POINT)
  end

  def clear_empty_rows!
    @array.reject! { |row| row.all? { |el| el == EMPTY_SQUARE } }
  end

  def populate_area(area, pos)
    #puts "Populating #{area}... at #{pos}"
    @array[pos[1]][pos[0]] = area.render

    area.rendered = true

    area.connections.each_for_render(pos) do |area, offset|
      populate_area(area, offset)
    end
  end
end

STARTING_AREA = Area.get('Yamaki Town')
STARTING_POINT = [1, 5]

puts Map.new
puts Area::Legend