require 'colorize'

EMOTIONS = [
  %w|Smile Smirk Angry Frown EyesClosed EyesClosedGrin|,
  %w|Rant SlightSmile Sneaky Devilish Question Crying|,
  %w|Sleeping SmileClosedMouth DrunkGrin WipedOutGrin Alarmed Wink|,
  %w|Unamused Blush Rage Dazed Sweat Annoyed|,
].freeze

ROW_SIZE = 6
PORTRAIT_HEIGHT = 42
PORTRAIT_WIDTH = 39

file = ARGV[0]

unless file
  puts "Specify a filename to split."
  exit
end

file = file[2..-1] if file && file.start_with?('.\\')

file.match /^([a-z0-9]+)/
Dir.mkdir($1) unless Dir.exist?($1)

EMOTIONS.each_with_index do |row, y|
  row.each_with_index do |emotion, x|
    crop_dims = "#{PORTRAIT_WIDTH}x#{PORTRAIT_HEIGHT}+#{x * PORTRAIT_WIDTH}+#{y * PORTRAIT_HEIGHT}"
    system `magick convert #{file} -crop #{crop_dims} -gravity center -background #70c0a0 -extent 64x64 #{$1}/#{emotion.downcase}.png`
  end

end

puts "Check output.txt."

File.open('output.txt', 'w') do |f|
  f.puts <<~C
    /* #{"Cool! I've created your files. Now, insert the following into the character definitons of portrait.c".red} */

    /* #{$1.capitalize} Portraits */

    #define PORTRAIT_#{$1.upcase} <index in characters list>
    static const u8 gPortrait#{$1.capitalize}Name[] = _("#{$1.capitalize}");
    static const u32 gPortrait#{$1.capitalize}Pal[] = INCBIN_U32("<palette file here>");
    #{EMOTIONS.flatten.map do |e|
      <<~C
        static const u32 gPortrait#{$1.capitalize}#{e}Gfx[] = INCBIN_U32("graphics/portraits/#{$1.downcase}/#{e.downcase}.4bpp.lz");
      C
    end.join('')}

    /* #{"Next, add this at the end of gPortraitList[]".red} */

    PORTRAIT_ENTRY(#{$1.capitalize})
  C
end