
# project tuxvision ( and my code Library )

# Roadmap of this hobbist project

### Exploring, Learning and write a set of C++ framework of (from my own) libraries

## core support classes ( namespace tuxvision ) main directory( for ex.: #include <tuxvision/string.h>)

    - [class tux::string]
        Composite accumulator for serializing and formatting supported components into its container - std::string.
    - [tux::color]
        Ansi (and future HTML) colours mnemonics and renderers
    - [rem :  return enumrated mnemonic]
        Coherant and consistent global return code meaningful mnemonics.
        Also used by the messaging system and journals.
    - [class tux::signals::notify; tux::signals::signotify ]
        C++ template header for basic signal-slots - A modified copy of :
        https://schneegans.github.io/tutorials/2015/09/20/signal-slot
        -> Not fully multi-threads yet, but I am starting to explore using a working notify signals across threads.
    - [class tux::ui::application]
        Base application class..., will holds and manage the config data of the components and events queu, and will manage a threads pool.
    - [ tux::ui::geometry classes ]
        {tux::ui::cxy, tux::ui::size, tux::ui::rectangle, tux::ui::string2d} Bare 2D geometry components.
    - [class  tux::object]
        Base Object class on the parent-child relational journalistic ( smart-pointers not used there - Too much overload (yet?) )
    -[class  tux::glyph and  tux::accent_fr]
        Actually, some hardcoded unicode and french accent glyphes. Waiting to find a coherant and a definitive easy to use unicode API.
    -[tux::cmd::cmd_switch tux::cmd::line,  with notify-hook]
        Developping my own command-line arguments processor.
        -> It is very hard to create a coherent realistic model. POSIX or not, the syntax is a mess because there is NO format rules excepted white space separators and confused quotes and subshell/commands tokens.
    
---
---
copyrights ...,2025,... Serge Lussier
