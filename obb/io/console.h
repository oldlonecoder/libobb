/******************************************************************************************
 *   Copyright (C) ...,2024,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/


#pragma once

#include <obb/io/vchar.h>
#include <obb/notify.h>
#include <obb/object.h>
//#include <tuxvision/geometry.h>
#include <obb/io/listener.h>
#include <obb/io/kbhit.h>
#include <obb/io/ansi_parser.h>
#include <termios.h>

// https://www.xfree86.org/current/ctlseqs.html
#define SET_X10_MOUSE 9
#define SET_VT200_MOUSE 1000
#define SET_VT200_HIGHLIGHT_MOUSE 1001
#define SET_BTN_EVENT_MOUSE 1002
#define SET_ANY_EVENT_MOUSE 1003
// --------------------------------------------

namespace obb::io
{

class OBBIOLIB console
{

    CLASSNAME(console);
    u8 _flags{0};
    u8 _state{0};

    ui::cxy            _cursor_pos{0,0};

    static constexpr u8 st_saved         = 1;
    static constexpr u8 st_mouse_enabled = 2;
    static constexpr u8 st_activated     = 4;
    static constexpr u8 st_raw_set       = 8;
    static constexpr u8 st_poll_started  = 0x10;
    static constexpr u8 st_poll_closed   = 0x20;
    static constexpr u8 st_caret_on      = 0x40;


    int _epoll_fd{-1};
    ui::rectangle _window{};    ///< Virtual console buffers size.
    ui::size      _phys_size{}; ///< Physical console Width|Height.
    ui::cxy       _window_pos{};///< topleft position of the console buffer in the _window.
    static termios  saved_st, new_term;
    signals::notify_action<ui::rectangle> _window_resize_signal{"console resize signal notifier"};
    static void resize_signal(int );

    io::listener _listener{}; ///< Open persistent (program's life-time) epoll fd.

public:

    static constexpr u8 use_mouse               = 1;
    static constexpr u8 report_mouse_position   = 2;
    static constexpr u8 report_mouse_buttons    = 4;
    static constexpr u8 use_double_buffer       = 8;    ///< Also tells console to save and clear the initial screen then restore it at exit.
    static constexpr u8 auto_hide_caret         = 0x10; ///< Hide the caret when not on keyboard input prompt.


    enum caret_shapes: u8
    {
        def,
        bloc_blink,
        block_steady,
        under_blink,
        under_steady,
        vbar_blink,
        vbar_steady
    }cursor_shape{def};



    static constexpr auto LINE_WRAP                 = "7";
    static constexpr auto CRS_SHAPE                 = "25";
    static constexpr auto MOUSE_X10                 = "9 ";
    static constexpr auto SET                       = 'h';
    static constexpr auto RESET                     = 'l';
    static constexpr auto MOUSE_VT200               = "\x1b[?1000";
    static constexpr auto MOUSE_VT200_HL            = "\x1b[?1001";
    static constexpr auto MOUSE_REPORT_BUTTONS      = "\x1b[?1002";
    static constexpr auto MOUSE_REPORT_ANY          = "\x1b[?1003";
    static constexpr auto MOUSE_UTF8                = "\x1b[?1005";
    static constexpr auto MOUSE_SGR_EXT_MODE        = "\x1b[?1006";
    static constexpr auto MOUSE_URXVT_MODE          = "\x1b[?1015";
    static constexpr auto MOUSE_SGR_PIXEL_MODE      = "\x1b[?1016";
    static constexpr auto ALTERNATE_SCREEN          = "\x1b[?1049";
    static constexpr auto CSI                       = "\x1b[";
    static constexpr auto CSI_BOLD                  = "\x1b[1m";
    static constexpr auto CSI_UNDERLINE             = "\x1b[4m";
    static constexpr auto CSI_REVERSE               = "\x1b[7m";
    static constexpr auto CSI_STRIKETHROUGH         = "\x1b[35m";
    static constexpr auto CSI_UNDERLINE_PREVIOUS    = "\x1b[90m";
    static constexpr auto CSI_UNDERLINE_NEXT        = "\x1b[92m";
    static constexpr auto CSI_UNDERLINE_INCREMENT   = "\x1b[93m";
    static constexpr auto CSI_UNDERLINE_DECREMENT   = "\x1b[94m";


    signals::notify_action<ui::rectangle>& term_resize_signal();

    //rem::cc update_widget(object* _widget);

    console()=default;
    explicit console(const std::string& name,u8 _flags_=0);

    ~console();



    static rectangle geometry();
    static rem::cc enable_mouse();
    static rem::cc stop_mouse();
    static rem::cc query_winch();
    static rem::cc begin();
    static rem::cc end();

    static void switch_alternate();
    static void switch_back();
    static void clear();
    static void cursor_off();
    static void cursor_on();
    static void cursor(ui::cxy xy);
    //static rem::cc mv(ui::direction::type dir=ui::direction::right, int d=1);

    static rem::cc render(vchar::bloc* blk, ui::cxy xy={0,0});
    static rem::cc init_stdinput();
    static std::pair<rem::cc, io::ansi_parser::input_data> poll_in();
private:

    rem::action parse_stdin(io::lfd& ifd);

};


} //namespace tux::io
