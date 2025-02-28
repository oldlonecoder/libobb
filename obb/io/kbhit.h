/******************************************************************************************
*   Copyright (C) ...,2025,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club / lussier.serge@gmail.com                            *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (Serge Lussier), unless otherwise specified.   *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/



#pragma once

#include <map>
#include <vector>
#include <obb/logbook.h>
//#include <obb/io/export.h>
#include <obb/io/lfd.h>


namespace obb::io
{

using namespace obb::integers;


struct OBBIOLIB kbhit
{

    enum enums : u8
    {
        ARROW_UP,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        ENTER,
        ESCAPE,
        BACKSPACE,
        DELETE,
        HOME,
        PAGE_UP,
        PAGE_DOWN,
        END,
        TAB,
        INSERT,
        F1         ,
        F2         ,
        F3          ,
        F4          ,
        F5          ,
        F6          ,
        F7          ,
        F8          ,
        F9          ,
        F10         ,
        F11         ,
        F12         ,
        SHIFT_F1,
        SHIFT_F2     ,
        SHIFT_END    ,
        SHIFT_HOME   ,
        SHIFT_ARROW_UP,
        SHIFT_ARROW_DOWN,
        SHIFT_ARROW_LEFT,
        SHIFT_ARROW_RIGHT,
        SHIFT_F3,
        SHIFT_F4,
        SHIFT_F5,
        SHIFT_F6,
        SHIFT_F7,
        SHIFT_F8,
        SHIFT_F9,
        SHIFT_F10,
        SHIFT_F11,
        SHIFT_F12,
        SHIFT_CTRL_ARROW_LEFT,
        SHIFT_CTRL_ARROW_RIGHT,
        SHIFT_CTRL_ARROW_UP,
        SHIFT_CTRL_ARROW_DOWN,
        CTRL_ARROW_LEFT,
        CTRL_ARROW_RIGHT,
        CTRL_ARROW_UP,
        CTRL_ARROW_DOWN,
        CTRL_INSERT,
        CTRL_HOME,
        CTRL_A,
        CTRL_B,
        CTRL_C,
        CTRL_D,
        CTRL_E,
        CTRL_F,
        CTRL_G,
        CTRL_H,
        CTRL_J,
        CTRL_K,
        CTRL_L,
        CTRL_M,
        CTRL_N,
        CTRL_O,
        CTRL_P,
        CTRL_Q,
        CTRL_R,
        CTRL_S,
        CTRL_T,
        CTRL_U,
        CTRL_V,
        CTRL_W,
        CTRL_X,
        CTRL_Y,
        CTRL_Z,
        CTRL_MINUS,
        CTRL_POBB,
        CTRL_PERIOD,
        CTRL_SLASH,
        CTRL_BACKSLASH,
        CTRL_BACKSPACE,
        SHIFT_TAB,
        SHIFT_ENTER,
        CTRL_F8,
        SHIFT_CTRL_DEL,
        SHIFT_CTRL_HOME,
        SHIFT_ALT_ARROW_LEFT,
        SHIFT_ALT_ARROW_RIGHT,
        SHIFT_ALT_ARROW_UP,
        SHIFT_ALT_ARROW_DOWN,
        SHIFT_ALT_END,
        SHIFT_ALT_HOME,
        SHIFT_ALT_PAGE_UP,
        SHIFT_ALT_PAGE_DOWN,
        CTRL_ALT_A,
        CTRL_ALT_B,
        CTRL_ALT_C,
        CTRL_ALT_D,
        CTRL_ALT_E,
        CTRL_ALT_F,
        CTRL_ALT_G,
        CTRL_ALT_H,
        CTRL_ALT_J,
        CTRL_ALT_K,
        CTRL_ALT_L,
        CTRL_ALT_M,
        CTRL_ALT_N,
        CTRL_ALT_O,
        CTRL_ALT_P,
        CTRL_ALT_Q,
        CTRL_ALT_R,
        CTRL_ALT_S,
        CTRL_ALT_T,
        CTRL_ALT_U,
        CTRL_ALT_V,
        CTRL_ALT_W,
        CTRL_ALT_X,
        CTRL_ALT_Y,
        CTRL_ALT_Z,
        CTRL_ALT_MINUS,
        CTRL_ALT_POBB,
        CTRL_ALT_PERIOD,
        CTRL_ALT_SLASH,
        CTRL_ALT_BACKSLASH,
        CTRL_ALT_BACKSPACE,
        SHIFT_PAGE_UP,
        SHIFT_PAGE_DOWN,
        CTRL_PAGE_UP,
        CTRL_PAGE_DOWN,
        CTRL_DELETE,
        CTRL_END,
        ALT_ARROW_LEFT,
        ALT_ARROW_RIGHT,
        ALT_ARROW_UP,
        ALT_ARROW_DOWN,
        CTRL_ALT_ARROW_LEFT,
        CTRL_ALT_ARROW_RIGHT,
        CTRL_ALT_ARROW_UP,
        CTRL_ALT_ARROW_DOWN,

        //...
        CHARACTER,
        NO_KEY,
    };

    struct OBBIOLIB state
    {
        u8 shift : 1;
        u8 ctrl  : 1;
        u8 alt   : 1;
        u8 sup   : 1;
    }kst{0,0,0,0};

    u64 code{0};
    kbhit::enums       mnemonic{kbhit::NO_KEY};
    std::string_view name{"NO_KEY"};

    kbhit() = default;
    ~kbhit() = default;

    kbhit(kbhit::enums e,  u64 c, std::string_view n);

    kbhit(kbhit&& kb_ref)= default;
    kbhit& operator=(kbhit&& kb_ref)noexcept = default;
    kbhit(const kbhit& kb_ref)=default;
    kbhit& operator=(const kbhit& kb_ref)=default;

    explicit operator bool() const;

    using refdb = std::map<kbhit::enums, kbhit>;
    using textdb = std::map<std::string_view, kbhit>;

    using dbgroup = std::vector<kbhit>;
    static dbgroup keys_db;

    static kbhit query(u64 bytes_seq);
    static kbhit query(std::string_view s);
    static std::pair<rem::cc, kbhit> test(lfd& _fd);
    static kbhit NONE;

private:


};


} // namespace lux::io
