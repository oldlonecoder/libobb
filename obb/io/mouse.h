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
#include <obb/io/lfd.h>
#include <obb/geometry.h>

namespace obb::io
{


/*!
 * \brief The mouse data struct
 *
 */
struct OBBIOLIB mouse
{


    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_UP
    /// ex.: button.left == mouse::BUTTON_UP;
    static constexpr u8 BUTTON_UP = 0;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_PRESSED
    /// ex.: button.left == BUTTON_PRESSED;
    static constexpr u8 BUTTON_PRESSED = 2;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_DOWN
    /// ex.: button.left == mouse::BUTTON_DOWN;
    static constexpr u8 BUTTON_DOWN = 1;
    ///////////////////////////////////////////////////////////////////////////////////////
    /// \brief BUTTON_RELEASE
    /// ex : button.left == BUTTON_RELEASE;
    static constexpr u8 BUTTON_RELEASE = 3;

    mouse()=default;
    ~mouse() = default;

    mouse(const mouse& cpy) = default;
    mouse(mouse&& mref) noexcept = default;

    mouse& operator=(const mouse& cpy) = default;
    mouse& operator=(mouse&& mref) noexcept = default;

    struct OBBIOLIB buttons
    {
        u8 left  : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
        u8 mid   : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
        u8 right : 2; // 0 = up; 1 = down; 2 = pressed event; 3 = released event;
    }button{0,0,0};

    struct OBBIOLIB
    {
        u8 shift :1;
        u8 alt   :1;
        u8 win   :1;
    }state{0,0,0};

    ui::cxy pos{};
    ui::cxy dxy{};

    bool left   (){return button.left;}
    bool middle (){return button.mid;}
    bool right  (){return button.right;}

    mouse& operator & (const mouse& mev);


};

} // namespace obb::io


