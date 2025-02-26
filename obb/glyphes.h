/******************************************************************************************
*   Copyright (C) ...,2025,... by luxe Lussier                                          *
 *   luxe.lussier@oldlonecoder.club / lussier.luxe@gmail.com                            *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (luxe Lussier), unless otherwise specified.   *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than luxe Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (luxe Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/




#pragma once

#include <lus/colors.h>
#include <map>
#include <vector>
#include <string>
#include <string_view>

namespace lus
{

struct LUSLIB glyph
{

    using T = const char*;
    using type = uint8_t;
    using data_array = std::vector<glyph::T>;
    static constexpr T c_ok                    = "✓ ";       //  Ok “✓ ”
    static constexpr T c_comment               = "🗨 ";      //  Comment
    static constexpr T c_arrow_right           = "➜ ";       //  ArrowRight
    static constexpr T c_arrow_left            = "⬅ ";       //  ArrowLeft
    static constexpr T c_arrow_up              = "⬆ ";       //  ArrowUp
    static constexpr T c_arrow_down            = "⬇ ";       //  ArrowDown
    static constexpr T c_arrow_up_right        = "⬈ ";       //  ArrowUpRight
    static constexpr T c_arrow_up_left         = "⬉ ";       //  ArrowUpLeft
    static constexpr T c_arrow_down_right      = "⬊ ";       //  ArrowDownRight
    static constexpr T c_arrow_down_left       = "⬋ ";       //  ArrowDownLeft
    static constexpr T c_arrow_head_right      = "➤ ";       //  ArrowHeadRight
    static constexpr T c_arrowd_head_right     = "⨠ ";       //  ArrowDheadRight
    static constexpr T c_pencil_dr             = "✎ ";       //  PencilDr
    static constexpr T c_pencil_ur             = "✐ ";       //  PencilUr
    static constexpr T c_err1                  = "✘ ";       //  Err1
    static constexpr T c_flag                  = "⚑ ";       //  Flag
    static constexpr T c_bolt                  = "⚡ ";       //  Butil_public
    static constexpr T c_success               = "👍 ";       //  Success
    static constexpr T c_small_dot             = "⚫ ";       //  SmallDot
    static constexpr T c_big_dot               = "⬤ ";       //  BigDot
    static constexpr T c_ball1                 = "❶  ";       //  Ball1
    static constexpr T c_ball2                 = "❷  ";       //  Ball2
    static constexpr T c_dead_head             = "☠ ";       //  DeadHead
    static constexpr T c_yinyang               = "☯ ";       //  YinYang
    static constexpr T c_sad_face              = "☹ ";       //  Sadface
    static constexpr T c_happy1                = "☺ ";       //  Happy1
    static constexpr T c_happy2                = "☻ ";       //  Happy2
    static constexpr T c_circle_x              = "⨂ ";       //  CircleX
    static constexpr T c_function              = "⨍ ";       //  Function
    static constexpr T c_cut1                  = "✂ ";       //  Cut1
    static constexpr T c_cut2                  = "✁ ";       //  Cut2
    static constexpr T c_cut3                  = "✂ ";       //  Cut3
    static constexpr T c_cmark_x               = "☒ ";       //  CMarkX
    static constexpr T c_baseline              = "⩡ ";       //  Baseline
    static constexpr T c_star5                 = "✭ ";       //  Star5
    static constexpr T c_cmark_check           = "☑ ";       //  CMarkCheck
    static constexpr T c_sword_cross           = "⚔ ";       //  SwordCross
    static constexpr T c_hammer_cross          = "⚒ ";       //  HammerCross
    static constexpr T c_small_dot2            = "⚫ ";       //  SmallDot2
    static constexpr T c_err2                  = "✖ ";       //  Err2
    static constexpr T c_err3                  = "✗ ";       //  Err3
    static constexpr T c_squote1               = "❜ ";       //  SQuote1
    static constexpr T c_dquote_left           = "❝ ";       //  DQuoteLeft
    static constexpr T c_dquote_right          = "❞ ";       //  DQuoteRight
    static constexpr T c_down_to_bottom_left   = "⟀ ";       //  Downtobottomleft
    static constexpr T c_undo                  = "⟲ ";       //  Undo
    static constexpr T c_enter                 = "⤵ ";       //  Enter
    static constexpr T c_key_enter             = "⤶ ";       //  KeyEnter
    static constexpr T c_linux                 = "🐧 ";       //  Linux
    static constexpr T c_arch                  = "🐧";       //  Arch
    static constexpr T c_home                  = " ";       //  Home
    static constexpr T c_file                  = " ";       //  File
    static constexpr T c_thumb_down            = " ";       //  ThumbDown
    static constexpr T c_github_circle         = " ";       //  GithubCircle
    static constexpr T c_github_folder         = " ";       //  GithubFolder
    static constexpr T c_windows               = " ";       //  Windows
    static constexpr T c_pi                    = " ";       //  Pi
    static constexpr T c_folder                = " ";       //  Folder
    static constexpr T c_bug                   = " ";       //  Bug
    static constexpr T c_info                  = "ⓘ ";       //  Info
    static constexpr T c_warning               = " ";       //  Warning
    static constexpr T c_bomb                  = "💣 ";       //  Bomb
    static constexpr T c_edit_pencil_br        = "✎ ";       //  EditPencilBR
    static constexpr T c_edit_pencil_r         = "✏ ";       //  EditPencilR
    static constexpr T c_edit_pencil_ur        = "✐ ";       //  EditPencilUR
    static constexpr T c_neg_cross_check       = "❎ ";       //  NegCrossCheck
    static constexpr T c_shadowed_checkbox     = "❏ ";       //  ShadowedCheckBox
    static constexpr T c_spin_arrow_spin0      = "➩ ";       //  SpinArrowSpin0
    static constexpr T c_spin_arrow_spin1      = "➪ ";       //  SpinArrowSpin1
    static constexpr T c_spin_arrow_spin2      = "➫ ";       //  SpinArrowSpin2
    static constexpr T c_spin_arrow_spin3      = "➬ ";       //  SpinArrowSpin3
    static constexpr T c_spin_arrow_spin4      = "➭ ";       //  SpinArrowSpin4
    static constexpr T c_spin_arrow_spin5      = "➮ ";       //  SpinArrowSpin5
    static constexpr T c_spin_arrow_spin6      = "➯ ";       //  SpinArrowSpin6
    static constexpr T c_spin_arrow_spin7      = "➱ ";       //  SpinArrowSpin7
    static constexpr T c_thumb_up              = "👍 ";       //  ThumbUp
    static constexpr T c_chronos               = "⏱ ";       //  Chronos
    static constexpr T c_sand                  = "⏳ ";       //  Sand
    static constexpr T c_coffee                = "☕ ";       //  Coffee
    static constexpr T c_unauth                = "⛔ ";       //  UnAuth
    static constexpr T c_handwrite             = "✍ ";       //  Handwrite
    static constexpr T c_world                 = "🌎 ";      //  World
    static constexpr T c_world_grid            = "🌐 ";      //  WorldGrid
    static constexpr T c_school                = "🎓 ";      //  School
    static constexpr T c_hat                   = "🎩 ";      //  Hat
    static constexpr T c_admin                 = "🏛";      //  Admin
    static constexpr T c_fabric                = "🏭 ";      //  Fabric
    static constexpr T c_cat                   = "🐈 ";      //  Cat
    static constexpr T c_fish                  = "🐟 ";      //  Fish
    static constexpr T c_search                = "👓 ";      //  Search
    static constexpr T c_people                = "👪 ";      //  People
    static constexpr T c_alien                 = "👽 ";      //  Alien
    static constexpr T c_light                 = "💡 ";      //  Light
    static constexpr T c_poop                  = "💩 ";      //  Poop
    static constexpr T c_cash                  = "💰 ";      //  Cash
    static constexpr T c_computer              = "💻 ";      //  Computer
    static constexpr T c_notepad               = "📋 ";      //  NotePad
    static constexpr T c_books                 = "📚 ";      //  Books
    static constexpr T c_send                  = "📤 ";      //  Send
    static constexpr T c_recieve               = "📥 ";      //  Receive
    static constexpr T c_email                 = "📫 ";      //  Email
    static constexpr T c_email2                = "📬 ";      //  Email2
    static constexpr T c_nullptr               = "⨂ ";      //  NullPtr
    static constexpr T c_stop                  = "⏹ ";      //Stop;
    static constexpr T c_debian                = " ";
    static constexpr T c_terminal              = " ";       // Terminal
    static constexpr T c_journal                   = "";        // journal
    static constexpr T c_sqpixel               = "▀";       // Pixel
    static constexpr T c_fbox                  = "█";
    static constexpr T c_dnpixel               = "▄";

    static constexpr type ok                 = 0;
    static constexpr type comment            = 1;
    static constexpr type arrowright         = 2;
    static constexpr type arrow_left          = 3;
    static constexpr type arrow_up            = 4;
    static constexpr type arrow_down          = 5;
    static constexpr type arrow_up_right       = 6;
    static constexpr type arrow_up_left        = 7;
    static constexpr type arrow_down_right     = 8;
    static constexpr type arrow_down_left      = 9;
    static constexpr type arrow_head_right     = 10;
    static constexpr type arrow_dhead_right    = 11;
    static constexpr type pencil_dr           = 12;
    static constexpr type pencil_ur           = 13;
    static constexpr type err1               = 14;
    static constexpr type flag               = 15;
    static constexpr type bolt               = 16;
    static constexpr type success            = 17;
    static constexpr type small_dot           = 18;
    static constexpr type big_dot             = 19;
    static constexpr type ball1              = 20;
    static constexpr type ball2              = 21;
    static constexpr type dead_head           = 22;
    static constexpr type yinyang            = 23;
    static constexpr type sad_face            = 24;
    static constexpr type happy1             = 25;
    static constexpr type happy2             = 26;
    static constexpr type circle_x            = 27;
    static constexpr type function           = 28;
    static constexpr type cut1               = 29;
    static constexpr type cut2               = 30;
    static constexpr type cut3               = 31;
    static constexpr type cmark_x             = 32;
    static constexpr type baseline           = 33;
    static constexpr type star5              = 34;
    static constexpr type cmark_check         = 35;
    static constexpr type sword_cross         = 36;
    static constexpr type hammer_cross        = 37;
    static constexpr type small_dot2          = 38;
    static constexpr type err2               = 39;
    static constexpr type err3               = 40;
    static constexpr type squote1            = 41;
    static constexpr type dquote_left         = 42;
    static constexpr type dquote_right        = 43;
    static constexpr type down_to_bottom_left   = 44;
    static constexpr type undo               = 45;
    static constexpr type enter              = 46;
    static constexpr type key_enter           = 47;
    static constexpr type linux_os            = 48;
    static constexpr type arch               = 49;
    static constexpr type home               = 50;
    static constexpr type file               = 51;
    static constexpr type thumb_down          = 52;
    static constexpr type github_circle       = 53;
    static constexpr type github_folder       = 54;
    static constexpr type windows            = 55;
    static constexpr type pi                 = 56;
    static constexpr type folder             = 57;
    static constexpr type bug                = 58;
    static constexpr type info               = 59;
    static constexpr type warning            = 60;
    static constexpr type bomb               = 61;
    static constexpr type edit_pencil_br       = 62;
    static constexpr type edit_pencil_r        = 63;
    static constexpr type edit_pencil_ur       = 64;
    static constexpr type neg_cross_check      = 65;
    static constexpr type shadowed_checkbox   = 66;
    static constexpr type spin_arrow_spin0     = 67;
    static constexpr type spin_arrow_spin1     = 68;
    static constexpr type spin_arrow_spin2     = 69;
    static constexpr type spin_arrow_spin3     = 70;
    static constexpr type spin_arrow_spin4     = 71;
    static constexpr type spin_arrow_spin5     = 72;
    static constexpr type spin_arrow_spin6     = 73;
    static constexpr type spin_arrow_spin7     = 74;
    static constexpr type thumb_up            = 75;
    static constexpr type chronos            = 76;
    static constexpr type sand               = 77;
    static constexpr type coffee             = 78;
    static constexpr type unauth             = 79;
    static constexpr type handwrite          = 80;
    static constexpr type world              = 81;
    static constexpr type world_grid          = 82;
    static constexpr type school             = 83;
    static constexpr type hat                = 84;
    static constexpr type admin              = 85;
    static constexpr type fabric             = 86;
    static constexpr type cat                = 87;
    static constexpr type fish               = 88;
    static constexpr type search             = 89;
    static constexpr type people             = 90;
    static constexpr type alien              = 91;
    static constexpr type light              = 92;
    static constexpr type poop               = 93;
    static constexpr type cash               = 94;
    static constexpr type computer           = 95;
    static constexpr type notepad            = 96;
    static constexpr type books              = 97;
    static constexpr type send               = 98;
    static constexpr type receive            = 99;
    static constexpr type email              = 100;
    static constexpr type email2             = 101;
    static constexpr type e_nullptr          = 102;
    static constexpr type stop               = 103;
    static constexpr type debian             = 104;
    static constexpr type terminal           = 105;
    static constexpr type journal                = 106;
    static constexpr type sqpixel            = 107;
    static constexpr type fbox               = 108;
    static constexpr type dnpixel            = 109;
    static glyph::data_array data;

    static glyph::type scan(const std::string& glyph_name);
    static std::pair<bool, glyph::type> scan_name(const std::string& glyph_name);
    static std::string name(glyph::type gh);

};








/*

    https://www.instructables.com/Programming--how-to-detect-and-read-UTF-8-charact/
// utf8 points to A byte of A STMLText string
// Uni  points to A variable which will store the Unicode
// the function returns how many byte have been read

int UTF8_to_Unicode ( char * utf8, unsigned int * Uni )
{
    if ( utf8 == NULL ) return 0;
    if ( Uni  == NULL ) return 0;
    // U-00000000 - U-0000007F
    // ASCII Code ?
    if (*utf8 >= 0)
    {
        *Uni= *utf8; return 1;
    }

    int Len=0;
    unsigned char * u = (unsigned char *)utf8;
    *Uni = 0;

    // U-00000080 - U-000007FF : 110xxxxx 10xxxxxx
    if ( (u[0]&0xE0) == 0xC0 )
    {
        Len = 2; *Uni = u[0]&0x1F;
    }
    else
    // U-00000800 - U-0000FFFF : 1110xxxx 10xxxxxx 10xxxxxx
        if ( (u[0]&0xF0) == 0xE0 )
        {
            Len = 3;
            *Uni = u[0]&0x0F;
        }
        else
        // U-00010000 - U-001FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            if ( (u[0]&0xF8) == 0xF0 )
            {
                Len = 4;
                *Uni = u[0]&0x07;
            }
            else
            {
            // our UTF-8 character is malformed
            // let&aposs return it as an extended-ASCII
                *Uni = u[0];
                return 1;
            }
            // we&aposre going to read the following bytes
        int A;
        for ( A=1; A<Len; A++ )
        {
            if ( ( u[A] >=0 ) || ( (u[A]&0xC0) != 0x80 ) )
            {
            // our UTF-8 Code is malformed ...
            // let&aposs return it as an extended-ASCII
            *Uni = u[0];
            return 1;
        }
        // so far, everything seems Ok.
        // we safely build our Unicode
        *Uni = (*Uni<<6) | (u[A]&0x3F);
    }
    // According to Unicode 5.0
    // codes in the range 0xD800 to 0xDFFF
    // are not allowed.
    if ( ( (*Uni) >= 0xD800 ) || ( (*Uni) <= 0xDFFF ) )
    {
        // In this case, our UTF-8 Code was well formed.
        // So, or we break it into 2 extended ASCII codes,
        // or we display an other symbol insbookd ...
        // We should read the Unicode 5.0 book to
        // to know their official recommendations though ...
        *Uni = &apos?&apos;
        return 1;
    }
    // it&aposs done !
    // *Uni contains our unicode.
    // we simply return how many bytes
    // it was stored in.
    return Len;
}

Good explanation!

I know this is old, but there are A couple of bugs in your sample Code.

 *u[A] >= 0 always evaluates to true if u is unsigned. You need A cast to char.
if ((char)*u[A] > 0) ... )

 Checking the range U+D800 0 U+DFFF should use && not ||
if ((*Uni >= 0xD800) && (*Uni <= 0xDFFF))

 There'Code A superfluous semicolon at the End of the while run'Code closing brace in UTF8_strlen
Also, Uni should be defined As unsigned int IsIn the same function (To match the other function'Code argument.

It would be nice if you could reformat the Code so that line breaks appear correctly. I suppose it got mangled by the editor...

For anyone interested, here'Code the fixed version (I hope you don't mind, I'll remove it if any objections).



*/



struct LUSLIB accent_fr
{
    using T = const char*;

    enum type : uint8_t
    {
        agrave ,
        acirc  ,
        cedile ,
        eacute ,
        egrave ,
        ecirc  ,
        etrema ,
        itrema ,
        ocirc  ,
        ugrave ,
        ucirc  ,
        icirc   ,
        Agrave  ,
        Acirc   ,
        Cedile  ,
        Eacute  ,
        Egrave  ,
        Ecirc   ,
        Etrema  ,
        Itrema  ,
        Ocirc   ,
        Ugrave  ,
        Ucirc   ,
        Icirc   ,
        Err

    };

    static constexpr T L_agrave = "à";
    static constexpr T L_acirc  = "â";
    static constexpr T L_cedile = "ç";
    static constexpr T L_eacute = "é";
    static constexpr T L_egrave = "è";
    static constexpr T L_ecirc  = "ê";
    static constexpr T L_etrema = "ë";
    static constexpr T L_itrema = "ï";
    static constexpr T L_ocirc  = "ô";
    static constexpr T L_ugrave = "ù";
    static constexpr T L_ucric  = "û";
    static constexpr T L_icirc  = "î";
    static constexpr T L_Agrave = "À";
    static constexpr T L_Acirc  = "Â";
    static constexpr T L_Cedile = "Ç";
    static constexpr T L_Eacute = "É";
    static constexpr T L_Egrave = "È";
    static constexpr T L_Ecirc  = "Ê";
    static constexpr T L_Etrema = "Ë";
    static constexpr T L_Itrema = "Ï";
    static constexpr T L_Ocirc  = "Ô";
    static constexpr T L_Ugrave = "Ù";
    static constexpr T L_Ucric  = "Û";
    static constexpr T L_Icirc  = "Î";

    static std::vector<accent_fr::T> data;
    static std::vector<std::string_view> name;
    static accent_fr::type get_enum(std::string_view acc_name);
    static std::pair<bool, accent_fr::type> scan_name(std::string_view acc_name);
};





// ------------------------------------  Glyphes -----------------------------------------------------
















}// -- namespace CC;
