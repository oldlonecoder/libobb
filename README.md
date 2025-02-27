
# project libobb++ ( and my code Library )

# Roadmap of this hobbyist project

### Exploring, Learning and write a set of C++ framework of (from my own) libraries

## core support classes ( namespace obb ) main directory( for ex.: #include <obb++/string.h>)

    - [class obb::string]
        Composite accumulator for serializing and formatting supported components into its container - std::string.
    - [obb::color]
        Ansi (and future HTML) colours mnemonics and renderers
    - [rem :  return enumrated mnemonic]
        Coherant and consistent global return code meaningful mnemonics.
        Also used by the messaging system and journals.
    - [class obb::signals::notify; obb::signals::signotify ]
        C++ template header for basic signal-slots - A modified copy of :
        https://schneegans.github.io/tutorials/2015/09/20/signal-slot
        -> Not fully multi-threads yet, but I am starting to explore using a working notify signals across threads.
    - [ obb::ui::geometry classes ]
        {obb::ui::cxy, obb::ui::size, obb::ui::rectangle, obb::ui::string2d} Bare 2D geometry components.
    - [class obb::object]
        Base Object class on the parent-child relational journalistic ( smart-pointers not used there - Too much overload (yet?) )
    -[class  obb::glyph and  obb::accent_fr]
        Actually, some hardcoded unicode and french accent glyphes. Waiting to find a coherant and a definitive easy to use unicode API.
    -[obb::cmd::cmd_switch obb::cmd::line,  with notify-hook]
        Developping my own command-line arguments processor.
        -> It is very hard to create a coherent realistic model. POSIX or not, the syntax is a mess because there is NO format rules excepted white space separators and confused quotes and subshell/commands tokens.
    
---
...more descriptions to come.
---
copyrights ...,2025,... Serge Lussier
