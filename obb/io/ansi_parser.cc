

#include <obb/io/ansi_parser.h>

namespace obb::io
{



std::pair<rem::cc, ansi_parser::input_data> ansi_parser::parse(lfd &_fd)
{
    data = {};
    if(_fd.empty())
        return {rem::cc::empty,{}};
    /////////////////////////////////////////////////////
    /// Input size is 1: Either {CTRL/ALT/Command +}CHAR or ESCAPE:
    if(_fd.size() == 1)
    {
        _kf = true;
        if(data.kev = kbhit::query(*_fd); data.kev)
            return{rem::cc::accepted, data};
        data.kev = {kbhit::CHARACTER, *_fd, "char"};
        return {rem::cc::ready, data};
    }
    /////////////////////////////////////////////////////

    // We start CSI here : Keyboard or Mouse report:
    if(*_fd != 0x1b)
    {
        book::status() << "unknown or unhandled input sequence from the console." << book::eol;
        return {rem::cc::notimplemented,{}};
    }

    return {rem::cc::notimplemented,{}};

}


//////////////////////////////////////////////////////////////////////////////////////
/// \brief ansi_parser::parse_kbhit
/// \param _fd
/// \return
///
std::pair<rem::cc, ansi_parser::input_data> ansi_parser::parse_kbhit(lfd &_fd)
{
    return {rem::cc::notimplemented, {}};
}


////////////////////////////////////////////////////////////////////////////////////////
/// \brief ansi_parser::parse_mouse
///
/// Extract from https://www.xfree86.org/current/ctlseqs.html:
/// ... For example, motion into cell x,y with button 1 down is reported as CSI M @ C x C y . ( @ = 32 + 0 (button 1) + 32 (motion indicator) ).
/// ----------------------------------------------------------------------------------------------------------------------------------------
/// \param _args
/// \return
///
std::pair<rem::cc, ansi_parser::input_data> ansi_parser::parse_mouse(std::vector<int> &&_args)
{
    // pressed 'flag' ignored. Relying on the XTerm Button and meta state byte which reports buttons on the lasts two bits:
    book::debug() << book::endl;
    mouse mev{};

    if (_args.size() != 3){
        book::error() << " missing or extra arguments : expected 3, got " << color::yellow << _args.size() << book::eol;
        return {rem::cc::rejected,{}};
    }

    //////////////////////////////////////////////////////////////////////
    /// Assign the current buttons state, Adjust the button event on the previous mouse data
    mev.button.left   = (_args[0] & 3) == 0 ? 1 :0;
    mev.button.mid    = (_args[0] & 3) == 1 ? 1 :0;
    mev.button.right  = (_args[0] & 3) == 2 ? 1 :0;
    ///@todo Handle the other buttons...
    /// ...

    mev.state.shift     = (_args[0] & 4   ) != 0;
    mev.state.alt       = (_args[0] & 8   ) != 0;
    mev.state.win       = (_args[0] & 0x10) != 0;

    if(mev.state.alt)
        book::info() << color::pair({.fg=color::grey100, .bg=color::red4}) << "meta" << book::endl;
    // Subtract 1 from the coords. Because the terminal starts at 1,1 and our ui system starts 0,0
    mev.pos.x = _args[1]-1;
    mev.pos.y = _args[2]-1;
    //mev.move = console::mev().pos != mev.pos;
    //mev.dxy = {mev.pos.x-console::mev().pos.x, mev.pos.y-console::mev().pos.y};
    //book::info() << "mouse data:" << mev.to_string() << book::endl;

    return {rem::cc::ready,{mev}};
}


////////////////////////////////////////////////////////////////////
/// \brief ansi_parser::parse_args
/// \param _fd
/// \return
///
// std::pair<rem::cc, std::vector<int> > ansi_parser::parse_args(lfd &_fd)
// {

//     return {rem::cc::notimplemented, {}};
// }

std::pair<rem::cc, ansi_parser::input_data> ansi_parser::parse_csi(lfd &_fd)
{
    u8 b{0};
    int arg{0};
    std::vector<int> args{};
    if(*_fd != 0x1b)
    {
        book::error() << rem::cc::expected << " ESC code on the buffer at the current position." << book::eol;
        return {rem::cc::rejected,{}};
    }
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
                    type = ansi_parser::MEV;
                    return parse_mouse(std::move(args));
                case 'R':
                    book::warning() <<" R :Caret report - ignored" << book::eol;
                    return {rem::cc::notimplemented,{}};
                default:
                    book::error() << " Unhandled csi sequence. " << book::eol;
                    break;
            }
            return {rem::cc::unhandled,{}};
        }

    }while(!_fd.empty());
    return {rem::cc::unhandled,{}};
}

} // namespace obb::io
