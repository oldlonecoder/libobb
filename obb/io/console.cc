
#include <obb/rem.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>


#include <obb/io/console.h>

//#include <thread>
//#include <mutex>
#include <csignal>

//#include <obb/io/ansi_parser.h>
//

namespace obb::io
{

termios  console::saved_st{}, console::new_term{};



signals::notify_action<rectangle>& console::term_resize_signal()
{
    return _window_resize_signal;
}


static console* _console{nullptr};


rem::cc console::query_winch()
{
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    if((!win.ws_col)||(!win.ws_row))
        return rem::cc::notexist;

    _console->_window = rectangle{{0,0}, ui::size{static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)}};
    book::message() << " (new) terminal size: ["
                       << color::yellow << std::format("{:>3d}x{:<3d}",_console->_window.dwh.w,_console->_window.dwh.h)
                       << color::reset << "]" << book::endl;

    return rem::cc::done;
}


rectangle console::geometry() { return _console->_window; }



/*!
* \brief
    Instant call to this function when the system's console resize event occured.
    We take its new geometry and then notify connected hooks
* \author  Serge Lussier ( serge.lussier@oldlonecoder.club )
*/

void console::resize_signal(int )
{
    if (!_console)
        throw book::exception() [book::error() << "console::resize_signal: no console instance was set." << rem::action::commit];

    console::query_winch();
    _console->_window_resize_signal(_console->_window);
}


console::console(const std::string& name, u8 _flags_):_flags(_flags_) { _console = this; }


/*!
    @brief (static) console::begin()
        tuxvision console setup

    @author  Serge Lussier ( serge.lussier@oldlonecoder.club )
*/
rem::cc console::begin()
{
    if(auto c = console::query_winch(); !c)
        book::error() << rem::cc::failed << " to get the screen geometry - there will be no boudaries checks. " << book::endl;


    tcgetattr(STDIN_FILENO, &saved_st);
    new_term = saved_st;

    new_term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | IGNCR | IXON );
    new_term.c_oflag &= ~OPOST;
    new_term.c_cflag |= (CS8);
    new_term.c_cflag &= ~PARENB;
    new_term.c_lflag &= ~(ICANON | ECHO | IEXTEN | TOSTOP | ECHONL);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;
    new_term.c_cc[VSTART] = 0;
    new_term.c_cc[VSTOP] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

    //switch_alternate();

    book::write() << " console set to raw mode..." << book::endl;

    ::signal(SIGWINCH, &console::resize_signal);
    if(_console->_flags & console::use_double_buffer)
        switch_alternate();
    //cursor_off();
    enable_mouse();


    return rem::cc::done;
}

rem::cc console::end()
{
    if(_console->_flags & console::use_double_buffer)
        switch_back();

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_st);
    cursor_on();
    stop_mouse();

    return rem::cc::done;
}

void console::switch_alternate()
{
    std::cout << "\x1b[0m\x1b[?1049h" << std::flush;
    _console->_flags |= console::st_saved;
}

void console::switch_back()
{
    std::cout << "\x1b[0m\x1b[?1049l" << std::flush;
    _console->_flags &= ~console::st_saved;
}


/**
 * @brief Set terminal to report the mouse events.

    @note Execute CSI on each parameters because I realized that "\x1b[?1000;1002;...h" is not working.
 *
 */
rem::cc console::enable_mouse()
{
    //std::cout << MOUSE_VT200            << console::SET;
    //std::cout << MOUSE_REPORT_BUTTONS   << SET;
    std::cout << MOUSE_REPORT_ANY       << SET << std::flush;
    //std::cout << MOUSE_SGR_EXT_MODE     << SET;
    //std::cout << MOUSE_URXVT_MODE       << SET << std::flush;
    _console->_flags |= console::use_mouse;

    return rem::cc::accepted;
}

rem::cc console::stop_mouse()
{
    //std::cout << MOUSE_VT200            << RESET;
    //std::cout << MOUSE_REPORT_BUTTONS   << RESET;
    std::cout << MOUSE_REPORT_ANY       << RESET << std::flush;
    //std::cout << MOUSE_SGR_EXT_MODE     << RESET;
    //std::cout << MOUSE_URXVT_MODE       << RESET << std::flush;

    _console->_flags &= ~console::use_mouse;

    return rem::cc::accepted;
}


void console::clear()
{
    std::cout << "\x1b[2J";
}


void console::cursor_off()
{
    std::cout << "\x1b[?25l" << std::flush;
    _console->_flags &= ~console::st_caret_on;
}


/*!
 * @brief (Re-)activate the screen cursor.
 *
 */
void console::cursor_on()
{
    std::cout << "\x1b[?25h" << std::flush;
    _console->_flags |= console::st_caret_on;
}




void console::cursor(ui::cxy xy)
{
    std::cout << std::format("\x1b[{:d};{:d}H", xy.y+1,xy.x+1);
}

void mv(ui::direction::type dir, int d)
{
    char ch = dir == ui::direction::right ? 'C': dir==ui::direction::left  ? 'D' : dir==ui::direction::up    ? 'A' : 'B';
    std::cout << "\x1b[" << d << ch;
}






console::~console()
    = default;


rem::cc console::render(vchar::bloc* blk, ui::cxy xy)
{

    for (int y=0; y < blk->dim.height<int>(); y++){
        console::cursor({xy.x, xy.y+1+y});
        std::cout << vchar::render_line(blk->buffer->begin() + (*blk->dim.width<>() * y), *blk->dim.width<>());
    }
    std::cout << std::flush;
    return rem::cc::done;

}


static io::mouse mev{};

/*!
 * @brief Blocking console stdin input listener & loop.
 * @return rem::cc
 */
rem::cc console::init_stdinput()
{
    if(auto r = _console->_listener.open(); !r)
        return r;
    auto [r,ifd] = _console->_listener.attach({"stdin",STDIN_FILENO,1024,io::lfd::IMM|io::lfd::READ, EPOLLIN|EPOLLHUP|EPOLLERR});

    //ifd.set_read_notify(_console, &console::parse_stdin);
    ifd.activate();
    return rem::cc::ready;
}

std::pair<rem::cc, io::ansi_parser::input_data> console::poll_in()
{
    //@todo:
    //try{
    //    auto& fd = _console->_listener[STDIN_FILENO];
    //}
    //catch(book::exception e)
    //{
        // rethrow ? ...
    //    return {rem::cc::null_ptr, {}};
    //}

    auto [r, in] = _console->_listener.query_lfd(0);
    if(!r)
        throw  book::exception() [ book::except() << " console std input was not initialized prior to call this" << book::eol];

    if(auto r = _console->_listener.poll(0); !r){
        book::status() << "input data :" << r << book::eol;
        return {r,{}};
    }

    io::ansi_parser parser;
    auto [c,dt] = parser.parse(in);
    if(dt.is<kbhit>())
    {
        book::info() << " Key input :" << color::yellow << dt.data.kev.name << color::z << color::z << book::eol;
        if(dt.data.kev.code == kbhit::ESCAPE) return {rem::cc::terminate, dt};
    }

    if(dt.is<io::mouse>()){
        dt.data.mev.button.left = (
            mev.button.left != dt.data.mev.button.left ? (
                dt.data.mev.button.left ? io::mouse::BUTTON_PRESSED
                                   : io::mouse::BUTTON_RELEASE
                ) : dt.data.mev.button.left
        );
        dt.data.mev.button.right = (
            mev.button.right != dt.data.mev.button.right ? (
                dt.data.mev.button.right ? io::mouse::BUTTON_PRESSED
                                    : io::mouse::BUTTON_RELEASE
                ) : dt.data.mev.button.right
        );
        dt.data.mev.button.mid = (
            mev.button.mid != dt.data.mev.button.mid ? (
                dt.data.mev.button.mid ? io::mouse::BUTTON_PRESSED
                                  : io::mouse::BUTTON_RELEASE
                ) : dt.data.mev.button.mid
        );

        dt.data.mev.dxy = dt.data.mev.pos - mev.pos;
        mev = dt.data.mev;
        return {rem::cc::ready, dt};
    }
    if(dt.is<io::kbhit>())
        if(dt.data.kev.code==io::kbhit::ESCAPE) return {rem::cc::terminate, dt};


    return {rem::cc::unhandled,dt};
}


}// namespace lux::io
