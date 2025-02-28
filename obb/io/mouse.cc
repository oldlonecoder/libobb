#include <obb/io/mouse.h>
#include <bitset>

namespace obb::io
{




////////////////////////////////////////////////////////////////////////
/// \brief mouse::operator &
/// \param mev
/// \return
/// \note This method is called once the latest mouse data is assigned to this instance so we can evaluate the mouse events according to the comparison against mev
mouse& mouse::operator &(const mouse &mev)
{
    if(std::bitset<2>(mev.button.left) != std::bitset<2>(button.left)){
        // event on left button:
        button.left = mev.button.left == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }
    if(std::bitset<2>(mev.button.right) != std::bitset<2>(button.right)){
        // event on right button:
        button.right = mev.button.right == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }
    if(std::bitset<2>(mev.button.mid) != std::bitset<2>(button.mid)){
        // event on middle button:
        button.mid = mev.button.mid == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }

    dxy = pos - mev.pos;
    // todo : Where do I put mouse move event ??
    return *this;
}


mouse mouse::mev{};
///////////////////////////////////////////////////////////////////
/// \brief mouse::test
/// \param _fd
/// \return
/// \note Requiers that the first byte in _fd must be 0x1b and consumed.
///
std::pair<rem::cc, mouse> mouse::test(lfd &_fd)
{
    u8 b{0};
    int arg{0};
    std::vector<int> args{};
    book::status() << "csi begin:" << book::eol;
    do{
        _fd >> b;
        if(b == '<'){
            book::write() << "Altered [ ignored as of now ]" << book::eol;
            //...
            continue;
        }

        if(std::isdigit(b)){
            arg *=10; // Shift 10'th slide
            arg += b - '0';
            continue;
        }

        if(b ==';'){
            args.push_back(arg);
            arg = 0;
            continue;
        }

        // CSI is terminated by a character in the range 0x40–0x7E
        // (ASCII @A–Z[\]^_`a–z{|}~),
        // Note: I don't remember why we exclude '<'
        // To handle F1-F4, we exclude '['.
        if ((b >= '@') && (b <= '~') && (b != '<') && (b != '[')){
            args.push_back(arg);
            book::status() << "end csi sequence on '" << color::yellow << b << color::z << "' :" << book::eol;
            switch(b)
            {
                case 'M' : case 'm':
                    return parse(std::move(args));
                case 'R':
                    book::warning() <<" R :Caret report - ignored" << book::eol;
                    return {rem::cc::notimplemented,{}};
                default:
                    book::error() << " Unhandled csi sequence. " << book::eol;
                    break;
            }
            return {rem::cc::rejected,{}};
        }

    }while(!_fd.empty());
    return {rem::cc::unhandled,{}};
    return {rem::cc::notimplemented,{}};
}

std::pair<rem::cc, mouse> mouse::parse(std::vector<int> &&args_)
{
    // pressed 'flag' ignored. Relying on the XTerm Button and meta state byte which reports buttons on the lasts two bits:
                                                                                                                           book::debug() << book::endl;
    mouse mev{};

    if (args_.size() != 3){
        book::error() << " missing or extra arguments : expected 3, got " << color::yellow << args_.size() << book::eol;
        return {rem::cc::rejected,{}};
    }

    //////////////////////////////////////////////////////////////////////
    /// Assign the current buttons state, Adjust the button event on the previous mouse data
    mev.button.left   = (args_[0] & 3) == 0 ? 1 :0;
    mev.button.mid    = (args_[0] & 3) == 1 ? 1 :0;
    mev.button.right  = (args_[0] & 3) == 2 ? 1 :0;
    ///@todo Handle the other buttons...
    /// ...

    mev.state.shift     = (args_[0] & 4   ) != 0;
    mev.state.alt       = (args_[0] & 8   ) != 0;
    mev.state.win       = (args_[0] & 0x10) != 0;

    if(mev.state.alt)
        book::info() << color::pair({.fg=color::grey100, .bg=color::red4}) << "meta" << book::endl;
    // Subtract 1 from the coords. Because the terminal starts at 1,1 and our ui system starts 0,0
    mev.pos.x = args_[1]-1;
    mev.pos.y = args_[2]-1;
    return {rem::cc::ready,mev};
}



} // namespace obb::io

