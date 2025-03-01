
# project libobb++ ( my oldbitsnbytes c++ code Libraries )

# Roadmap of this hobbyist project

## Classes ( namespace obb ) main directory( for ex.: #include <obb++/string.h>)

    - [class obb::string]
        Composite accumulator for serializing and formatting supported components into its container - std::string.
    - [obb::color]
        Ansi (and future HTML) color mnemonics and renderer(s)
    - [rem : namespace rem : Return Enumrated Mnemonics]
        Coherant and consistent global meaningful return mnemonic codes.
        Also used by the messaging system and book logging journal.
    - [class obb::signals::notify; obb::signals::signotify ]
        C++ template header for basic signal-slots - A modified copy of :
        https://schneegans.github.io/tutorials/2015/09/20/signal-slot
        -> Not fully multi-threads yet, but I am starting to explore using a working notify signals across threads.
    - [ obb::ui::geometry classes ]
        {obb::ui::cxy, obb::ui::size, obb::ui::rectangle, obb::ui::string2d} Bare 2D geometry components.
    - [obb::book - ]
        logging and journaling output to file driven by the rem codes set.
    - [class obb::object]
        Base Object class on the parent-child relational logistic ( smart-pointers not used there - Too much overload (yet?) )
    -[class  obb::glyph and  obb::accent_fr]
        Actually, some hardcoded unicode and french accent glyphes. I am Waiting to find a coherant and a definitive easy to use unicode API.
    -[obb::cmd::cmd_switch obb::cmd::line,  with notify-hook]
        Developping very simple and quick custom command-line arguments processor.
        -> It is very hard to create a coherent realistic model. POSIX or not, the syntax is a mess because there is NO format rules excepted white space separators and confused quotes and subshell/commands tokens....
    - [obb::io::lfd obb::io::listener obb::io::console obb::io::kbhit obb::io::mouse obb::io::tcp_socket obb::io::vhcar]
        The custom, modest set of input-output api I am actually exploring, experimenting, writing...
    - [obb::lexer obb::token_data ...]
---
...more descriptions to come.
---
copyrights ...,2025,... Serge Lussier
