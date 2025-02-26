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
#include <lus/string.h>

namespace lus::ui
{

namespace justify
{
using Type = u16;
static constexpr u16 left        = 0x0001; ///< Justify left
static constexpr u16 right       = 0x0002; ///< Justify right
static constexpr u16 hcenter     = 0x0004; ///< Justify align horizontally at the center
static constexpr u16 vcenter     = 0x0008; ///< Justify Align vertically at the center
static constexpr u16 center      = 0x000C; ///< Justify Vertical and Horizontal center
static constexpr u16 word_wrap   = 0x0010; ///< Justify word wrap
static constexpr u16 prefix      = 0x0020; ///< Justify prefix
static constexpr u16 suffix      = 0x0040; ///< Justify suffix
static constexpr u16 auto_size   = 0x0080; ///< Justify auto-stretch
static constexpr u16 auto_size_text   = 0x0100; ///< Justify auto-stretch
}


/**
 * @brief lus::ui::rectangle enums values
 * @author &copy; 2008,2022,2023, Serge Lussier, lussier.serge@gmail.com ( oldlonecoder )
 */
namespace direction
{
using type = I8;
static constexpr I8 left = -1; ///< to left
static constexpr I8 right = 1; ///< to right
static constexpr I8 up = 2;    ///< up
static constexpr I8 down = -2; ///< down
}

struct LUSLIB cxy {

    int x = -1;
    int y = -1;

    using array = std::vector<cxy>;
    using iterator = cxy::array::iterator;
    using citerator = cxy::array::const_iterator;

    cxy() = default;
    cxy(cxy &&) noexcept = default;
    ~cxy() = default;
    cxy(int c_x, int c_y) : x(c_x), y(c_y){}
    cxy(const cxy &p) = default;
    cxy &operator=(const cxy &p) = default;
    cxy &operator-=(const cxy &dxy);
    cxy &operator+=(const cxy &dxy);
    bool operator==(cxy rhs) const;
    bool operator>(cxy rhs) const;
    bool operator<(cxy rhs) const;
    cxy operator+(const cxy &dxy) const;

    cxy operator+(int dx) const
    {
        return {dx + x, y};
    }
    [[nodiscard]] cxy get_max(const cxy &rhs) const;
    [[nodiscard]] cxy get_min(const cxy &rhs) const;
    cxy operator-(const cxy &rhs) const;
    [[nodiscard]] cxy lesser(cxy rhs) const;
    [[nodiscard]] cxy greater(cxy rhs) const;
    // cxy operator<<(cxy rhs) const;
    // cxy operator>>(cxy rhs) const;
    cxy &operator++();
    cxy &operator++(int);
    cxy &operator--();
    cxy &operator--(int);
    cxy &operator()(int x_, int y_);
    operator std::string() const;
};


struct LUSLIB size {
    int w{0};
    int h{0};
     
    // size policies:
    cxy min_size{};
    cxy max_size{};
    // --------------
    operator bool() const { return ((w > 0) && (h > 0)); }
    operator std::string() const;
    bool operator<(const size &dwh) const;
    bool operator==(const size &dwh) const;
    bool operator>(const size &dwh) const;
    bool operator!=(const size &dwh) const;
    void set_min_max(cxy mi, cxy ax);
    void set_min_size(int _w, int _h);
    void set_max_size(int _w, int _h);
    [[nodiscard]] int32_t area() const { return w*h;}
    bool has_minmax() const;
    bool has_min_size();
    bool has_max_size();

    template<typename T=int> std::optional<T> width() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(w         );
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(w        );
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(w           );
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(w  );
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(w          );
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(w );
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(w          );
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(w            );
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(w            );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(w           );
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(w           );
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(w        );// like u64
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(w           );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(w           );
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(w           );
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(w             );
        //journal::error() << journal::cc::expected << " compatible left-value type";
        return {};
    }
    template<typename T=int> std::optional<T> height() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(h);
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(h);
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(h);
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(h);
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(h);
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(h);
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(h);
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(h);
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(h);
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(h);  // like u64
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(h);
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(h);
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(h);
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(h);
        //journal::error() << journal::cc::expected << " compatible left-value type";
        return {};
    }
};


/*!
 * @brief Rectangular Geometry object (inspired by the Qt project, many, many years ago).
 *
 * It has evolved with my own point of view and limitations.
 * @li Provides internal Cursor relative coordinates
 * @li Still needs more limit implementations (min-max restrictions helpers)
 *
 * @author oldlonecoder (lussier.luxe@gmail.com)
 *
 */
struct LUSLIB rectangle {

    cxy a{0, 0};
    cxy b{0, 0};
    cxy cursor{0,0}; ///< inner cursor coordinates used by the location operations, relative to rectangle::a (topleft) coord.

    size dwh;
    bool nowrap = true;

    //static constexpr std::string_view    string_format = R"((\{3d},\{-3d})-[a:(\{3d},\{-3d}) b:(\{3d},\{-3d})]-[w:\{3d} h:\{-3d}])";  Disabled;

    using array = std::vector<rectangle>;
    using iterator = rectangle::array::iterator;
    using citerator = rectangle::array::const_iterator;

    rectangle() = default;
    ~rectangle() = default;
    rectangle(rectangle &&r) noexcept = default;
    rectangle(const rectangle &r) = default;
    rectangle(const cxy &a_, const cxy &b_);
    rectangle(const cxy &a_, const size &d);
    rectangle(int x, int y, int w, int h);
    explicit rectangle(const size &dxy);
    rectangle &operator=(rectangle &&r) noexcept = default;
    rectangle &operator=(const rectangle &r) = default;
    void assign(int x, int y, int w, int h);
    void assign(const cxy &a_, const cxy &b_);
    void assign(const cxy &a_, const size &dxy);
    cxy local();
    rectangle tolocal();
    cxy relative();
    void set_topleft(cxy pt);
    rectangle grow(cxy dxy);
    bool operator == (const rectangle& rhs) const;
    rectangle &operator+=(const cxy &dx);
    rectangle &operator-=(const cxy &dx);
    rectangle &operator|=(const rectangle& rhs);
    void resize(const size &new_sz);
    void moveat(const cxy &p);
    bool in(const cxy &pt) const;
    void move(const cxy &deltapt);
    std::tuple<cxy,cxy,ui::size> components() const { return {a, b,dwh}; }
    // [[nodiscard]] int width() const { return dwh.w; }
    // [[nodiscard]] int height() const { return dwh.h; }
    template<typename T=int> std::optional<T> width() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(dwh.w         );
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(dwh.w        );
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(dwh.w           );
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(dwh.w  );
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(dwh.w          );
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(dwh.w );
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(dwh.w          );
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(dwh.w            );
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(dwh.w            );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.w           );
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(dwh.w           );
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(dwh.w        );// like u64
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.w           );
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(dwh.w           );
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(dwh.w             );
        //journal::error() << journal::cc::expected << " compatible left-value type";
        return {};
    }
    template<typename T=int> std::optional<T> height() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(dwh.h);
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(dwh.h);
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(dwh.h);
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(dwh.h);
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(dwh.h);
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(dwh.h);
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(dwh.h);
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(dwh.h);
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(dwh.h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.h);
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(dwh.h);  // like u64
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(dwh.h);
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(dwh.h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.h);
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(dwh.h);
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(dwh.h);
        //journal::error() << journal::cc::expected << " compatible left-value type";
        return {};
    }

    bool operator[](const cxy &pt) const;
    cxy top_left()const;
    cxy top_right()const;
    cxy bottom_left()const;
    cxy bottom_right()const;
    [[nodiscard]] rectangle operator&(const rectangle &r) const;

    /*!
     * \brief operator / get the intersection between this and rhs then get the origin of this from rhs
     * \param rhs
     * \return result rectangle
     */
    rectangle operator/(const rectangle &rhs) const;

    /*!
        @brief merges this and r
    */
    rectangle operator|(const rectangle &r) const;
    rectangle operator+(const cxy &pt) const;
    rectangle operator-(const cxy &pt) const;
    [[nodiscard]] std::string tostring() const;
    operator std::string() const;
    operator bool() const { return (dwh); }//.operator bool();
    //------------- location operations ---------------------------------
    void home();
    bool operator++();
    bool operator++(int);
    bool operator--();
    bool operator--(int);
    bool goto_xy(cxy xy);
    cxy operator*() const
    { return cursor; }

};


struct LUSLIB string2d
{
    lus::string win{};
    rectangle r;

    string2d& gotoxy(int x, int y);
    string2d& operator<< (cxy xy);
    void set_geometry(int w, int h);

    // internal cursor movements:
    string2d& operator++();
    void operator++(int);
    string2d& operator--();
    void operator--(int);
    // --------------------------
    template<typename t> string2d& operator<< (t v)
    {
        lus::string str;
        str << v;
        return put(str());
    }




    string2d& put(const std::string& txt);

    void clear();
    std::string details();
    operator std::string();// {return win ? win->str() : "";}

};

}
