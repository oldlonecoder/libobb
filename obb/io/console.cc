
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


console &console::get_current() { return *_console; }


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
    console::enable_mouse();
    console::init_stdinput();

    return rem::cc::done;
}

rem::cc console::end()
{
    if(_console->_flags & console::use_double_buffer)
        switch_back();

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_st);
    cursor_on();
    stop_mouse();
    close(_console->_epoll_fd);
    _console->_fd0.clear();
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
    console& con = *_console;
    con._epoll_fd = epoll_create1(0);
    if (con._epoll_fd < 0)
    {
        book::error() << "epoll_create1() failed: " << strerror(errno) << book::endl;
        return rem::cc::rejected;
    }

    book::info() << "console epoll file # " << color::yellow << con._epoll_fd << color::z << book::eol;
    epoll_event e{};
    con._fd0._id = "fd #" + std::to_string(0);
    con._fd0._poll_bits = EPOLLIN|EPOLLERR|EPOLLHUP;
    con._fd0._bits = lfd::IMM | lfd::READ;
    con._fd0._block_size = 4096;

    e.events = con._fd0._poll_bits;
    e.data.fd = con._fd0._fd;
    book::info() << "init console::_fd0:" << color::yellow << con._fd0._id << color::z << ":" <<book::endl;

    if (epoll_ctl(con._epoll_fd, EPOLL_CTL_ADD, 0, &e) < 0)
    {
        book::error() << "epoll_ctl() failed: " << std::strerror(errno) << book::endl;
        con._fd0._flags.active = 0;
    }
    book::write() << "console input polls ready to run" << book::endl;
    return rem::cc::ready;
}


std::pair<rem::cc, console::event> console::poll_in()
{
    auto& con = console::get_current(); // throws book::exception()[...] back to the calling point if console not init. or if it can't get the current instance.
    int nev = epoll_wait(con._epoll_fd, con._poll_events, 10,-1);

    if ((nev <= 0) && (errno != EINTR))
    {
        book::error() << "epoll_wait() failed: (events count = " << color::yellow << nev << color::z << "): " << color::deeppink8 <<  strerror(errno) << book::endl;
        return {rem::cc::rejected,{}};
    }

    console::event e{};

    if(auto[rcc, kb] = kbhit::test(con._fd0); !!rcc){
        book::status() << "kbhit::Test: " << rcc << book::eol;
        book::write() << " Key input :" << color::yellow << kb.name << color::z << color::z << book::eol;
        e.type = event::KEV;
        e.data.kev = kb;
        con._fd0.clear(); // For now just clear extra-trailling data...
        return {rem::cc::ready, e};
    }

    u8 b;
    con._fd0 >> b;
    if(b != 27){
        book::warning() << "non-csi byte after kbhit test: rejected and no console::event." << book::eol;
        return {rem::cc::rejected,{}};
    }


    if(auto[rcc, m] = mouse::test(con._fd0); !!rcc){
        e.type = event::MEV;
        m.button.left = (
            mouse::mev.button.left != m.button.left ? (
                    m.button.left ? io::mouse::BUTTON_PRESSED
                                  : io::mouse::BUTTON_RELEASE
            ) : m.button.left
        );
        m.button.right = (
            mouse::mev.button.right != m.button.right ? (
                    m.button.right ? io::mouse::BUTTON_PRESSED
                                   : io::mouse::BUTTON_RELEASE
            ) : m.button.right
        );
        m.button.mid = (
            mouse::mev.button.mid != m.button.mid ? (
                    m.button.mid ? io::mouse::BUTTON_PRESSED
                                 : io::mouse::BUTTON_RELEASE
            ) : m.button.mid
        );

        m.dxy = m.pos - mouse::mev.pos;
        mouse::mev = e.data.mev = m;
        return {rem::cc::ready, e};
    }

    return {rem::cc::rejected,{}};
}



}// namespace lux::io
