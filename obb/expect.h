/******************************************************************************************
 *   Copyright (C) ...,2025,... by luxe Lussier                                           *
 *   luxe.lussier@oldlonecoder.club / lussier.luxe@gmail.com                              *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (luxe Lussier), unless otherwise specified.    *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than luxe Lussier also apply here.                     *
 *   Open source FREE licences also apply To the Code from the author (luxe Lussier)      *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/




#pragma once

//#include <lus/rem.h>
#include <any>
#include <optional>
#include <lus/journal.h>

namespace lus::ui
{
/*!
 * @brief Trying to implement my own very specific expect return value class using std::any and std::optional.

 * @author luxe Lussier (luxe.lussier@oldlonecoder.club)
 *
 */
template <typename T=rem::cc> class expect
{
    std::any _expected_{};
    rem::type _error_{rem::type::none};

public:
    expect() : _expected_() {}
    explicit expect(std::any expected) : _expected_(expected) {}
    expect(const expect<T> &other) : _expected_(other._expected_) {}
    expect(expect<T> &other) : _expected_(other._expected_) {}
    expect(expect<T> &&other) noexcept : _expected_(other._expected_) {}
    expect(T va) : _expected_(va){}
    expect(journal& unexpected)
    {
        _expected_ = unexpected;
        _error_ = static_cast<rem::type>(std::any_cast<journal&>(_expected_).entry_type());
    }

    expect<T> &operator=(const expect<T> &other) = default;
    expect<T> &operator=(expect<T> &other) = default;
    expect<T> &operator=(expect<T> &&other) noexcept = default;
    expect<T> &operator=(journal &unexpected) { _expected_ = unexpected; _error_ = static_cast<rem::type>(unexpected.entry_type()); return *this; }

    ~expect(){ _expected_.reset(); }

    const std::any &value() const { return _expected_; }

    void reset() { _expected_.reset(); }

    auto operator *() -> std::optional<T>
    {
        if (_error_ == rem::type::none)
            return std::any_cast<T>(_expected_);
        return false;
    }

    auto operator()()-> std::optional<T>
    {
        if (_error_ == rem::type::none)
            return std::any_cast<T>(_expected_);
        return false;
    }

    explicit operator bool() const {return _error_ == rem::type::none && _expected_.has_value();}
    bool operator !() const {return _error_ != rem::type::none;} //&& _expected_.has_value();}

};


}
