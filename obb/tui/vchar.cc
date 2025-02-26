//
// Created by oldlonecoder on 25-02-06.
//

#include <lus/ui/vchar.h>
#include <lus/journal.h>
//#include <lus/ui/console.h>


namespace lus::ui
{

#define _eol_ color::pair(color::reset, color::reset)()




#pragma region vchar-bloc
// ---------------------------------------------------------------------------------------------------------------------


//rem::cc vchar::bloc::render(const ui::rectangle& subrect)
//{
//    ui::rectangle rect=subrect;
//    if (!state)
//        return state;
//
//    if (!rect )
//        rect = dim;
//    if (!rect )
//    {
//        state = rem::cc::notready;
//        return state;
//    }
//
//    rect = rect & console::geometry();
//    if (!rect)
//    {
//        state = rem::cc::rejected;
//        return state;
//    }
//
//    auto local = rect.tolocal() + (rect.a-dim.a);
//
//    for (int y = 0; y < *rect.height(); y++)
//    {
//        console::cursor({rect.a.x, rect.a.y+y});
//        std::cout << vchar::render_line(buffer->begin() + (*rect.width<>() * y + local.a.x), *local.width<>());
//    }
//    state = rem::cc::accepted;
//    return state;
//}


// rem::cc vchar::bloc::render(console* con, const ui::rectangle& subrect)
// {
//     //...
//     return console::render(this);
// }


vchar::bloc& vchar::bloc::cursor(ui::cxy _pos)
{
    if (!dim.goto_xy(_pos))
    {
        state = rem::cc::oob;
        return *this;
    }
    state = rem::cc::accepted;
    return *this;
}


int vchar::bloc::line() const
{
    return dim.cursor.y;
}


int vchar::bloc::column() const
{
    return dim.cursor.x;
}


vchar::bloc& vchar::bloc::operator<<(const std::string& _str)
{
    if (_str.length() >= (buffer->end()-_c_))
        throw journal::exception()[ journal::except() << rem::type::fatal << rem::cc::oob];

    for (auto c: _str)
    {
        **_c_++ << c;
    }
    return *this;
}


vchar::bloc& vchar::bloc::operator<<(glyph::type _glyph)
{
    **_c_ << _glyph;
    return *this;
}


vchar::bloc& vchar::bloc::operator<<(color::code _color)
{
    _c_->set_bg(_color);
    return *this;
}


vchar::bloc& vchar::bloc::operator<<(color::pair _colors)
{
    **_c_ << _colors;
    return *this;
}


vchar::bloc& vchar::bloc::operator<<(cadre::index _frameindex)
{
    **_c_ << _frameindex;
    return *this;
}

/*!
 * @note bypasses natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge Lussier (oldlonecoder)
 */
bool vchar::bloc::operator++()
{
    if (++dim)
    {
        ++_c_;
        return true;
    }
    return false;
}


/*!
 * @note bypass natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge Lussier (oldlonecoder)
 */
bool vchar::bloc::operator++(int)
{
    if (++dim)
    {
        ++_c_;
        return true;
    }
    return false;
}


/*!
 *
 * @note bypass natural increment-decrement because this method is the convenient way to advance the internal cursor with our boundaries.
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge Lussier (oldlonecoder)
 */
bool vchar::bloc::operator--()
{
    if (--dim)
    {
        --_c_;
        return true;
    }
    return false;
}



/*!
 *
 * @return true if the cursor is within the boundaries  false otherwise.
 * @author Serge Lussier (oldlonecoder)
 */
bool vchar::bloc::operator--(int)
{
    if (--dim)
    {
        --_c_;
        return true;
    }
    return false;
}



vchar::bloc::~bloc()
{
    buffer->clear();
}


vchar::bloc::operator bool() const
{
    return !buffer->empty() && dim;
}


vchar::back_buffer vchar::bloc::create(const ui::size& _dim, color::pair _colours)
{
    auto sp = std::make_shared<vchar::string>(_dim.area(), vchar(color::pair(_colours)));
    dim = {{0,0},_dim};
    return sp;
}


void vchar::bloc::sync_cursors()
{
    auto  w = _c_ - buffer->begin();
    dim.cursor = {static_cast<int>(w) % *dim.width(),static_cast<int>(w) / *dim.width()};
    end_pos = dim.cursor;
}


#pragma endregion char32-bloc

// ---------------------------------------------------------------------------------------------------------------------




[[maybe_unused]] vchar::vchar(U32 Ch) : d(Ch){}

vchar::vchar(vchar* C): d(C->d){}

vchar::vchar(color::pair cc)
{
    set_colors(cc);
    d |= ASCII | 0x20&0xFF;
}


vchar &vchar::set_fg(color::code fg) { d = d & ~FGMask | static_cast<U8>(fg) << FGShift; return *this; }
vchar &vchar::set_bg(color::code bg) { d = d & ~BGMask | static_cast<U8>(bg) << BGShift; return *this; }
[[maybe_unused]] vchar &vchar::set_attributes(U32 ch) { d = (d & ~AttrMask) | ch; return *this; }
//[[maybe_unused]] vchar &vchar::set_colors(color::pair &&Ch) { return set_fg(Ch.fg).set_bg(Ch.bg); }

[[maybe_unused]] vchar &vchar::set_colors(const color::pair &CP)
{
    d = d & ~ColorsMask | static_cast<U8>(CP.fg) << FGShift | static_cast<U8>(CP.bg) << BGShift;
    return *this;
}

vchar &vchar::operator=(U32 Ch) { d = Ch; return *this; }

vchar &vchar::operator=(const U32* Ch) { d = *Ch; return *this; }


std::string vchar::get_utf_string() const
{
    if(d & UTFBITS)
    {
        switch(d & UTFBITS)
        {
        case UGlyph:
            return  glyph::data[icon_id()];
        case Accent:
            return  accent_fr::data[accent_id()];
        case Frame:
            return cadre()[frame_id()];
        default: break;
            //throw journal::exception() [journal::fatal() << " Memory corruption error into vchar data!"];
        }
    }
    std::string s;
    s += ascii();
    return s;
}


vchar &vchar::operator=(char Ch)
{
    d = d & ~(CharMask|UGlyph|Accent|Frame) | d & (CMask|Underline|Stroke|Blink|TRGB)  | ASCII | Ch & 0xff;
    return *this;
}

color::code vchar::foreground() const { return static_cast<color::code>((d & FGMask) >> FGShift); }
color::code vchar::background() const { return static_cast<color::code>((d & BGMask) >> BGShift); }
[[maybe_unused]] color::pair vchar::colors() const { return {foreground(),background()}; }

[[maybe_unused]] glyph::type vchar::icon_id() const
{
    if (!(d & UGlyph))
        throw journal::exception() [ journal::except() << rem::cc::rejected << "attempt to use this vchar cell as a glyph which is not,"];

    auto Ic = d & CharMask;
    if (Ic > glyph::journal)
        throw journal::exception()[journal::except() <<  rem::cc::oob << ':' << Ic];
    return  Ic;
}


[[maybe_unused]] accent_fr::type vchar::accent_id() const
{
    auto AID = d & CharMask;
    if (AID > accent_fr::Ucirc)
        throw journal::exception()[journal::fatal()  << rem::cc::oob << ':' << AID];

    return static_cast<accent_fr::type>(AID);
}




cadre::index vchar::frame_id() const
{
    auto c = d & 0xff;
    if(c > 11)
        throw journal::exception() [journal::except() << rem::cc::oob  << " invalid frame index: " << color::red4 << c];

    return static_cast<cadre::index>(d & 0xFF);
}

char vchar::ascii() const
{ return static_cast<char>(d & 0xff); }

[[maybe_unused]] uint16_t vchar::attributes() const
{ return (d & AttrMask) >> ATShift; }

vchar &vchar::operator<<(glyph::type gl)
{ d = (d & ~(UtfMask|CharMask))  | (d&ColorsMask)|UGlyph | (gl&0xFF); return *this; }

vchar &vchar::operator<<(accent_fr::type ac)
{ d = (d & ~(AttrMask|CharMask)) | (d & (Underline|Stroke|Blink|ColorsMask)) | Accent | ac; return *this; }

vchar& vchar::operator<<(cadre::index fr)
{ d = (d & ~(UtfMask|CharMask))  | (d&ColorsMask)|(fr&0xFF) | Frame; return *this; }

vchar& vchar::operator<<(color::pair cp)
{ d = (d & ~ColorsMask)          | static_cast<U8>(cp.fg) << FGShift | static_cast<U8>(cp.bg) << BGShift; return *this; }

vchar& vchar::operator<<(char Ch)
{ d = (d & ~(UTFBITS|CharMask))  | (d & (Underline|Stroke|Blink|ColorsMask)) | ASCII | (Ch & 0xff); return *this; }


[[maybe_unused]] std::string vchar::render_colors() const
{
    std::string str;
    str += color::render({background(),foreground()});
    return str;
}

vchar::operator std::string() const { return details(); }



// std::string vchar::render_line(const vchar::string& _string)
// {
//     return "vchar::render_line(const vchar::string& _string) is not implemented";
// }




std::string vchar::render_line(vchar::string::iterator _it, std::size_t count)
{
    color::pair current_colors = _it->colors();
    //journal::debug() << "iterator details:" << _it->details() << journal::eol;
    std::string _o = current_colors();
    auto c = _it;
    for(int x =0; x< count; x++)
    {
        vchar ch = *c++;
        auto  [fg, bg] = ch.colors();
        if(current_colors.bg != bg)
        {
            current_colors.bg = bg;
            _o += color::render_background(current_colors.bg);
        }
        if(current_colors.fg != fg)
        {
            current_colors.fg = fg;
            _o += color::render(current_colors.fg);
        }
        if(ch.d & UTFBITS)
        {
            if(ch.d & Frame)
                _o += cadre()[ch.frame_id()];
            else
                if(ch.d & Accent)
                    _o += accent_fr::data[ch.accent_id()];
                else
                    if(ch.d & UGlyph)
                    {
                        _o += glyph::data[ch.icon_id()];
                        _o += '\x08';
                    }
        }
        else
            _o += ch.ascii();
    }
    _o += _eol_;
    return _o;
}





std::string vchar::details() const
{

    lus::string infos;
    lus::string utf_info{};
    if(d & UTFBITS)
    {
        switch(d & UTFBITS)
        {
        case UGlyph:
            utf_info << "icon index:" << icon_id();
            break;
        case Accent:
            utf_info << "accent (fr) index:" << accent_id();
            break;
        case Frame:
            utf_info << "frame index:" << frame_id();
            break;
        default:break;
            //throw rem::exception() [rem::fatal() << " Memory corruption into screen::vchar data!"];
        }
    }
    else
        utf_info << ascii();
    infos << "| foreground color:" << foreground() << color::name(foreground()) << color::reset << "| background color:" << background() << color::name(background()) << color::reset;
    infos << " char:['" << colors() << utf_info() << color::reset <<  "']";
    if(d & Underline) infos << "|Underline";
    if(d & Stroke) infos << "|Stroke";
    if(d & Blink) infos << "|Blink";

    return infos();
}




} // namespace tux::io
