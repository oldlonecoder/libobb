//
// Created by oldlonecoder on 10/29/23.
//


#include <lus/geometry.h>
//#include <lus++/journal.h>



namespace lus::ui
{


#pragma region cxy

/**
 * @brief Subtract x,y by dxy
 *
 * @param dxy
 * @return cxy&
 */
cxy &cxy::operator-=(const cxy &dxy)
{
    x -= dxy.x;
    y -= dxy.y;
    return *this;
}

/**
 * @brief add dxy to this
 *
 * @param dxy
 * @return cxy&
 */
cxy &cxy::operator+=(const cxy &dxy)
{
    x += dxy.x;
    y += dxy.y;
    return *this;
}


string2d& string2d::operator<<(cxy xy)
{
    if(!r[xy])
    {
        //journal::error() << journal::code::oob << r << "; <-" << xy;
        return *this;
    }
    r.goto_xy(xy);
    return *this;
}


/**
 * @brief comparison
 *
 * @param rhs
 * @return true
 * @return false
 */
bool cxy::operator==(cxy rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}


/**
 * @brief add x,y with dxy then return the result
 *
 * @param dxy
 * @return cxy
 */
cxy cxy::operator+(const cxy &dxy) const
{
    return {dxy.x+x, dxy.y+y};
}

/**
 * @brief subtract x,y with dxy then return the result
 *
 * @param rhs
 * @return cxy
 */
cxy cxy::operator-(const cxy &rhs) const
{
    return {x-rhs.x, y-rhs.y};
}


/**
 * @brief ? alias to get_min...
 *
 * @param rhs
 * @return cxy
 */
cxy cxy::lesser(cxy rhs) const
{
    return get_min(rhs);
}

/**
 * @brief alias to get_max
 *
 * @param rhs
 * @return cxy
 */
cxy cxy::greater(cxy rhs) const
{
    return get_max(rhs);
}


/**
 * @brief Incoldloneluxent x immediately, cancelling natural behaviour
 *
 * @return ref to self
 */
cxy &cxy::operator++()
{
    ++x;
    return *this;
}


/**
 * @brief greater comparison operator
 *
 * @param rhs
 * @return true
 * @return false
 */
bool cxy::operator>(cxy rhs) const
{
    return (x>rhs.x) || (y>rhs.y);
}

/**
 * @brief lesser comparison operator
 *
 * @param rhs
 * @return true
 * @return false
 */
bool cxy::operator<(cxy rhs) const
{
    return (x<rhs.x) || (y<rhs.y);
}


/**
 * @brief Incoldloneluxent y immediately, cancelling natural behaviour
 *
 * @return ref to self
 */
cxy &cxy::operator++(int)
{
    ++y;
    return *this;
}

cxy &cxy::operator--()
{
    return *this;
}

cxy &cxy::operator--(int)
{
    return *this;
}

cxy &cxy::operator()(int x_, int y_)
{
    return *this;
}

cxy::operator std::string() const
{
    return std::format("{},{}", x,y);
}



/**
 * @brief get the max values of x,y between this and rhs
 *
 * @param rhs
 * @return cxy
 */
cxy cxy::get_max(const cxy &rhs) const
{
    return {x >= rhs.x ? x:rhs.x, y >= rhs.y ? y : rhs.y};
}


/**
 * @brief get the min values of x,y between this and rhs
 *
 * @param rhs
 * @return cxy
 */
cxy cxy::get_min(const cxy &rhs) const
{
    return {x < rhs.x ? x:rhs.x, y < rhs.y ? y : rhs.y};
}

#pragma endregion cxy

#pragma region size

size::operator std::string() const
{
    return std::format("{},{}:{}", w, h , w*h);
}


/**
 * @brief dimensions comparison...
 *
 * @param dwh
 * @return true
 * @return false
 */
bool size::operator<(const size &dwh) const
{
    return (w < dwh.w) || (h < dwh.h);
}


bool size::operator==(const size &dwh) const
{
    return (w==dwh.w) && (h==dwh.h);
}

bool size::operator>(const size &dwh) const
{
    return (w > dwh.w) || (h > dwh.h);
}

bool size::operator!=(const size &dwh) const
{
    return (w!=dwh.w) || (h!=dwh.h);
}


void size::set_min_max(cxy mi, cxy ax)
{
    min_size = mi;
    max_size = ax;
}


void size::set_min_size(int _w, int _h)
{
    min_size = { _w, _h };
}


void size::set_max_size(int _w, int _h)
{
    max_size = { _w, _h };
}


bool size::has_minmax() const { return min_size.x && min_size.y && max_size.x && max_size.y; }
bool size::has_min_size() { return min_size.x && min_size.y; }
bool size::has_max_size() { return max_size.x && max_size.y; }


#pragma endregion size

#pragma region rectangle


rectangle::operator std::string() const
{
    return std::format("{},{} [{},{}:{},{}; {}x{}]", cursor.x, cursor.y, a.x, a.y, b.x,b.y, dwh.w, dwh.h);
}

std::string rectangle::tostring() const
{
    return this->operator std::string();
}

void rectangle::home()
{
    cursor = {0, 0};
}

/*!
 * @brief advance the internal cursor by one unit.
 * @return true if accepted or false otherwise.
 */
bool rectangle::operator++()
{
    ++cursor.x;
    if (cursor.x > b.x) {
        if (nowrap) {
            --cursor.x;
            return false;
        }
        ++cursor.y;
        if (cursor.y > b.y) {
            cursor.y = b.y;
            //cursor.x = dwh.w-1;
            //journal::status() << " cursor wraps to home.";
            //cursor = a;
            return false;
        }
        cursor.x = a.x;
    }
    return true;
}

/*!
 * @brief  ++cursor.y
 * @return true or false if there was or not movement.
 */
bool rectangle::operator++(int)
{
    ++cursor.y;
    if (cursor.y > b.y) {
        if (nowrap) {
            --cursor.y;
            return false;
        }
        cursor.y = a.y;
    }
    return true;
}

bool rectangle::operator--()
{
    --cursor.x;
    if (cursor.x < a.x) {
        if (nowrap) {
            ++cursor.x;
            return false;
        }
        --cursor.y;
        if (cursor.y < a.y) {
            cursor.y = a.y;
            cursor.x = a.x;
            return false;
        }
        cursor.x = b.x;
    }
    return true;
}


bool rectangle::operator--(int)
{
    --cursor.y;
    if (cursor.y < a.y) {
        if (nowrap) {
            ++cursor.y;
            return false;
        }
        cursor.y = b.y;
    }
    return true;
}


/*!
 * @brief
 * @param p
 * @return
 * @note if cursor < r.a then p will not be assigned.
 */
bool rectangle::goto_xy(cxy xy)
{
    if (!in(xy + a)) {
        //journal::error() << "rejected at" << xy;
        return false;
    }
    cursor = xy;
    return true;
}

rectangle::rectangle(int x, int y, int w, int h)
{
    a = {x,y};
    dwh= { w, h };
    b = {a.x + dwh.w - 1, a.y + dwh.h - 1};
}


rectangle::rectangle(const cxy &a_, const cxy &b_)
{
    a = a_;
    b = b_;
    dwh.w = b.x - a.x + 1;
    dwh.h = b.y - a.y + 1;
}


/*!
 * \brief construct a rectangle from the size values.
 * \param wh
 */
rectangle::rectangle(const size &dxy)
{
    a = {0, 0};
    dwh = dxy;
    b = {a.x + dwh.w - 1, a.y + dwh.h - 1};
}


/*!
 * \brief construct a rectangle from the size values, at cxy a_.
 * \param a_
 * \param d
 */
rectangle::rectangle(const cxy &a_, const size &d)
{
    a = a_;
    dwh = d;
    b = {a.x + d.w - 1, a.y + d.h - 1};
}

void rectangle::assign(int x, int y, int w, int h)
{
    a = {x, y};
    b = {x + w - 1, y + h - 1};
    dwh = {w, h};
}

void rectangle::assign(const cxy &a_, const cxy &b_)
{
    a = a_;
    b = b_;
    dwh.w = b.x - a.x + 1;
    dwh.h = b.y - a.y + 1;
}

void rectangle::assign(const cxy &a_, const size &dxy)
{
    a = a_;
    dwh = dxy;
    b = {a.x + dxy.w - 1, a.y + dxy.h - 1};
}

rectangle &rectangle::operator+=(const cxy &dx)
{
    a += dx;
    b += dx;
    return *this;
}

rectangle &rectangle::operator-=(const cxy &dx)
{
    a -= dx;
    b.x -= dx.x;
    b.y -= dx.y;
    return *this;
}

rectangle &rectangle::operator|=(const rectangle &rhs)
{
    if(!rhs) return *this;
    *this = this->operator |(rhs);
    return *this;
}

void rectangle::resize(const size &new_sz)
{
    assign({a.x, a.y}, new_sz);
}

void rectangle::moveat(const cxy &p)
{
    a.x = p.x;
    a.y = p.y;
    b.x = a.x + dwh.w - 1;
    b.y = a.y + dwh.h - 1;
}

bool rectangle::in(const cxy &pt) const
{
    return ((pt.x >= a.x) && (pt.x <= b.x) && (pt.y >= a.y) && (pt.y <= b.y));
}

void rectangle::move(const cxy &deltapt)
{
    a += deltapt;
    b += deltapt;

}


bool rectangle::operator == (const rectangle& rhs) const
{
    return rhs.dwh.w == dwh.w && rhs.dwh.h == dwh.h;
}



/*!
 * \brief rectangle::operator []
 * Test is the xy coord is within the boundaries. Offset must be from the topleft value.
 * \param pt
 * \return true if within, false otherwise.

 * \author oldlonecoder (luxe.lussier@oldlonecoder.club; lussier.luxe@gmail.com)
 *
 * \note to test the internal cursor, pt must be set explicitely to cursor + a.
 */
bool rectangle::operator[](const cxy &pt) const
{
    return ((pt.x >= a.x) && (pt.x <= b.x) && (pt.y >= a.y) && (pt.y <= b.y));
}

cxy rectangle::top_left() const
{
    return a;
}

cxy rectangle::top_right() const
{
    return {b.x, a.y};
}

cxy rectangle::bottom_left() const
{
    return {a.x, b.y};
}

cxy rectangle::bottom_right() const
{
    return b;
}

/*!
    @brief intersection between this (a) and r (b).

    @note a & b must be on the same referential offset. undefined behaviour otherwise.
    @author &copy; 1996, 2023, luxe lussier, (oldlonecoder'@'gmail.com)
    @code
   a+==============================+
    |                              |
    |  b+==========================|===========+
    |   |                          |           |
    |   |                        +-|--+        |
    +============================|=+  |        |
        |                        |    |        |
        |                        +----+        |
        +======================================+
    @endcode

    @note to get target's inner coords after intersection, subtract from intersection the r.a of the target rectangle.
    ex: r1 & r2 := inter; inter <- r1 := inter.a - r1.a;
*/
rectangle rectangle::operator&(const rectangle &r) const
{
    if(!r) return {};
    auto topl = r.a - a;
    auto botr = r.b - b;
    rectangle tmp;

    tmp.assign(cxy{
        r.a.x > a.x ? r.a.x : a.x,
        r.a.y > a.y ? r.a.y : a.y
    },cxy{
        r.b.x > b.x ? b.x : r.b.x,
        r.b.y > b.y ? b.y : r.b.y
    });
    if((!in(tmp.a)) || (!in(tmp.b))) return {};

    return tmp;
}


/**
 * @brief  Intersect rhs with this. subtract a from result
 * then downscale result to local coordinates so
 *
 * @param rhs => rhs.a must be downscaled to relative coords on calling
 * @return rectangle
 */
rectangle rectangle::operator/(const rectangle &rhs) const
{
    rectangle tmp = *this & rhs;
    tmp -= a;


    return tmp;
}

rectangle rectangle::operator|(const rectangle &r) const
{
    rectangle tmp;
    // cxy a_ = {r.a.x <= a.x ? r.a.x : a.x, r.a.y <= a.y ? r.a.y : a.y};
    // cxy b_ = {r.b.x <= b.x ? r.b.x : b.x, r.b.y <= b.y ? r.b.y : b.y};
    cxy a_ = {std::min(r.a.x,a.x), std::min(r.a.y,a.y)};
    cxy b_ = {std::max(r.b.x,b.x), std::max(r.b.y,b.y)};

    tmp.assign(a_, b_);
    return tmp;
}

rectangle rectangle::operator+(const cxy &pt) const
{
    rectangle tmp = *this;
    tmp.a.x += pt.x;
    tmp.a.y += pt.y;
    tmp.b.x += pt.x;
    tmp.b.y += pt.y;
    tmp.dwh = dwh;
    return tmp;
}


rectangle rectangle::operator-(const cxy& pt) const
{
    rectangle r = *this;
    r.a.x-=pt.x;
    r.a.y-=pt.y;
    r.b.x-=pt.x;
    r.b.y-=pt.y;
    return r;
}


rectangle rectangle::grow(cxy dxy)
{
    rectangle r = *this;

    r.a.x -= dxy.x;
    r.b.x += dxy.x;
    r.a.y -= dxy.y;
    r.b.y += dxy.y;
    r.dwh.w = b.x - a.x + 1;
    r.dwh.h = b.y - a.y + 1;
    return r;
}

/*!
 * @brief return a local representation of the cursor position.
 * @return  local relative coords of the cursor.
 */
cxy rectangle::local()
{
    return {cursor.x - a.x, cursor.y - a.y};
}

cxy rectangle::relative()
{
    return cursor;
}

rectangle rectangle::tolocal()
{
    return {{0,0}, dwh};
}


#pragma endregion rectangle


//- -------------------------------- string2d ------------------------------------------------------------


string2d &string2d::gotoxy(int x, int y)
{
    r.goto_xy({x,y});
    return *this;
}

void string2d::set_geometry(int w, int h)
{
    r = rectangle({0,0}, size{w, h});
    clear();
}


string2d &string2d::operator++()
{
    ++r;
    return *this;
}

void string2d::operator++(int)
{
    r++;
}

string2d &string2d::operator--()
{
    --r;
    return *this;
}

void string2d::operator--(int)
{
   r--;
}

/// <summary>
/// luxe lussier
/// p = 3
/// 10-13 + 3;
///        *   luxe l*
/// </summary>
/// <param name="txt"></param>
/// <returns></returns>
string2d &string2d::put(const std::string &txt)
{
    auto w = r.width();
    if(!w) return *this;
    auto line_width = *w - r.cursor.x;
    auto ln = txt.length();

    auto dx = line_width <= ln ? line_width : ln;

    std::string::iterator crs = win.begin() + (r.cursor.y * *w + r.cursor.x);
    auto p = txt.begin();
    for (size_t x = 0; x < dx; x++)
        *crs++ = *p++;

    r.cursor.x += line_width;

    return *this;
}

void string2d::clear()
{
    auto w = r.width();
    auto h = r.height();

    win = std::string(*w * *h, ' ');
}

std::string string2d::details()
{
    string str = "string2d setails:\n";
    str << r.tostring() << " cursor: " << (std::string)r.cursor;
    return str();
}

string2d::operator std::string()
{
    std::string str;
    if (win.empty())
        return "oops! there is no such defined and initialised area!";
    str += '\n';
    auto w = r.width();
    auto h = r.height();

    if(!w||h) return str;

    for (int l = 0; l < *h; l++) {
        for (int c = 0; c < *w; c++)
            str += *(win.begin() + (l * *w + c));
        str += '\n';
    }
    return str;
}





}
