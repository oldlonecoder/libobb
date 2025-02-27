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


 #include <obb/logbook.h>
 #include <memory>
 #include <vector>
 #include <obb/geometry.h>
 #include <obb/io/export.h>

 using namespace obb::integers;

 namespace obb::io
 {

 class console;

 struct OBBIOLIB vchar
 {
     u32 d{0x8003A020};

     using string = std::vector<vchar>;
     using iterator = string::iterator;

     using back_buffer = std::shared_ptr<vchar::string>;


     /*!
      *  \brief console rectangular region for read and write to the console files: [ #0, #1, #2 ].
      *
      */

     static constexpr u32 CharMask  = 0x800000FF;
     static constexpr u32 FGMask    = 0x0000FF00;
     static constexpr u32 BGMask    = 0x00FF0000;
     static constexpr u32 CMask     = 0x00FFFF00;
     static constexpr u32 ColorsMask= 0x00FFFF00;
     static constexpr u32 AttrMask  = 0xFF000000;
     static constexpr u32 UtfMask   = 0xB10000FF;
     static constexpr u32 StyleMask = 0x0E000000;
     // ==============u===attributes==========================
     static constexpr u32 UGlyph    = 0x01000000;
     static constexpr u32 Underline = 0x02000000;
     static constexpr u32 Stroke    = 0x04000000;
     static constexpr u32 Blink     = 0x08000000;
     static constexpr u32 Accent    = 0x10000000;
     static constexpr u32 Frame     = 0x20000000;
     static constexpr u32 TRGB      = 0x40000000;
     /// This will maku use of true-color RGB command instead of the re-routed terminal GUI colors profile
     static constexpr u32 ASCII     = 0x80000000;
     static constexpr u32 UTFBITS   = Accent | Frame | UGlyph;
     // ==============Bit Shift ============================
     static constexpr int FGShift = 0x08;
     static constexpr int BGShift = 0x10;
     static constexpr int ATShift = 0x18;

     struct OBBIOLIB bloc
     {
         // --- CONFIGS AND INTERNAL DATA--------------
         color::pair             colours{};
         ui::rectangle           dim{};
         vchar::back_buffer      buffer{};
         ui::cxy                 end_pos{};
         rem::cc                 state{rem::cc::empty};
         vchar::string::iterator _c_{};

         // --- IO STUFF ------------------------------
         rem::cc             render(console* con, const ui::rectangle& subrect={});
         vchar::bloc&        cursor(ui::cxy _pos);
         [[nodiscard]] int   line() const;
         [[nodiscard]] int   column() const;

         vchar::bloc& operator << (const std::string& _str);
         vchar::bloc& operator << (glyph::type _glyph);
         vchar::bloc& operator << (color::code _color);
         vchar::bloc& operator << (color::pair _colors);
         vchar::bloc& operator << (cadre::index _frameindex);
         bool         operator ++();
         bool         operator ++(int);
         bool         operator --();
         bool         operator --(int);
         //...

         ~bloc();
         explicit operator bool() const;
         vchar::back_buffer create(const ui::size& _dim, color::pair _colours);
         void set_pos(ui::cxy xy) { dim.a = xy;}
         void sync_cursors();
     };


     vchar() = default;

     explicit vchar(U32 Ch);
     explicit vchar(vchar* C);
     vchar(vchar& C){d = C.d;}
     vchar(const vchar& C){d = C.d;}
     vchar(color::pair cc);
     ~vchar() = default;

     vchar& set_fg(color::code fg_);
     vchar& set_bg(color::code bg_);

     vchar& set_attributes(U32 Ch);
     //vchar& set_colors(color::pair&&Ch);
     // vchar& ResetAttributes(vchar::Type bits_);

     vchar& set_colors(const color::pair&CP);

     vchar& operator=(U32 Ch);
     vchar& operator=(const vchar& Ch) = default;
     vchar& operator=(const U32* Ch);
     vchar& operator=(char Ch);
     vchar& operator=(int Ch)
     {
         d = Ch;
         return *this;
     };

     [[nodiscard]] std::string get_utf_string() const;

     [[nodiscard]] color::code     foreground() const;
     [[nodiscard]] color::code     background() const;
     [[nodiscard]] color::pair     colors() const;
     [[nodiscard]] glyph::type     icon_id() const;
     [[nodiscard]] accent_fr::type accent_id() const;
     [[nodiscard]] cadre::index    frame_id() const;
     [[nodiscard]] char     ascii() const;
     vchar&  operator*() { return *this; }
     [[nodiscard]] uint16_t attributes() const;
     vchar& operator <<(glyph::type gl);
     vchar& operator <<(accent_fr::type ac);
     vchar& operator << (cadre::index fr);
     vchar& operator <<(color::pair cp);


     vchar& operator <<(vchar Ch)
     {
         d = Ch.d;
         return *this;
     }



     static std::string render_line(vchar::string::iterator _it, std::size_t count);
     static rem::cc render_bloc(vchar::bloc& blk, ui::cxy xy);

     vchar&     operator <<(char Ch);
     [[nodiscard]] std::string render_colors() const;
     explicit    operator std::string() const;
     [[nodiscard]] std::string details() const;


 };

 } // namespace obb::ui
