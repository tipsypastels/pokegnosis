Dragonsbreath.configure do |config|
  config.indent = '  '
  config.convert_ellipsis = true

  config.charmap_macros = {
    CHAR: ->match { 
      "{CHARACTER_COLOR}#{match}{NO_COLOR}"
    },
    MON: ->match { 
      "{POKEMON_COLOR}#{match}{NO_COLOR}"
    },
    PLACE: ->match { 
      "{LOCATION_COLOR}#{match}{NO_COLOR}"
    }
  }

  class ShowPortrait < OptionalWrapperCommand
    def expect_params(p)
      p.character :constant
      p.face :constant
    end

    def start
      "#{line.command} #{format(params.character)} #{format(params.face)}"
    end

    def close
      'hideportrait'
    end

    private

    def format(const)
      if const.value.start_with?('PORTRAIT_') 
        const.value
      else
        "PORTRAIT_#{const.value}"
      end
    end
  end

  class ShowPlayerPortrait < ShowPortrait
    def expect_params(p)
      p.face :constant
    end

    def start
      "#{line.command} #{format(params.face)}"
    end
  end

  config.register_command(:showportrait, ShowPortrait)
  config.register_command(:showplayerportrait, ShowPlayerPortrait)
end