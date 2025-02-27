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

#include <obb/glyphes.h>
#include <obb/string.h>

#include <source_location>

#include <functional>
#include <obb/geometry.h>
#include <filesystem>
#include <fstream>



using obb::ui::color;
using obb::glyph;
using obb::accent_fr;
using obb::ui::rectangle;
using obb::ui::cxy;
using obb::ui::size;






namespace obb
{

class object;

class OBBLIB book
{
public:
    struct header_component
    {
         integers::U8 type  : 1;
         integers::U8 stamp : 1;
         integers::U8 fun  : 1;
         integers::U8 file  : 1;
         integers::U8 line  : 1;
         integers::U8 col   : 1;
       //...
    };


private:
    rem::type _type_{};
    rem::cc _code_{};
    std::source_location location{};
    // ---------------------------------
    obb::string  text{};

    header_component _headercomp_{1,0,1,1,1,1};
public:


    enum oef : integers::u8 { eol,endl };
    static book& error       (std::source_location src = std::source_location::current());
    static book& warning     (std::source_location src = std::source_location::current());
    static book& fatal       (std::source_location src = std::source_location::current());
    static book& except      (std::source_location src = std::source_location::current());
    static book& message     (std::source_location src = std::source_location::current());
    static book& write       (std::source_location src = std::source_location::current());
    static book& debug       (std::source_location src = std::source_location::current());
    static book& info        (std::source_location src = std::source_location::current());
    static book& comment     (std::source_location src = std::source_location::current());
    static book& syntax      (std::source_location src = std::source_location::current());
    static book& status      (std::source_location src = std::source_location::current());
    static book& test        (std::source_location src = std::source_location::current());
    static book& interrupted (std::source_location src = std::source_location::current());
    static book& aborted     (std::source_location src = std::source_location::current());
    static book& segfault    (std::source_location src = std::source_location::current());
    static book& jnl         (std::source_location src = std::source_location::current());

    book& operator << (const std::string& txt);
    book& operator << (const char* txt);
    book& operator << (char ch);
    book& operator << (std::string_view txt);
    book& operator << (const rectangle& r);
    book& operator << (ui::cxy pt);
    book& operator << (color::code col);
    book& operator << (color::pair fgbg);
    book& operator << (glyph::type gh);
    book& operator << (accent_fr::type ac);
    book& operator << (rem::type ty);
    book& operator << (rem::cc cod);
    book& operator << (rem::fn fn);
    book& operator << (rem::action a_action);
    book& operator << (const obb::string::list& _list );
    book& operator << (book::oef e);
    book& operator << (const obb::string& str );
    template<typename T> book& operator << (const T& v)
    {
        text << v;
        return *this;
    }

    static std::vector<book> _mem_stream_;
    void init_header();
    static void purge(const std::function<void(book &)>& f);

    struct OBBLIB section
    {
        std::string id;   ///< Section ID which is also the base name of the output file.
        std::ofstream ofs;
        std::ofstream* fout{nullptr}; ///< will see.
        std::vector<book> contents{}; ///< Actual contents. Will be transferred into the entries container when the transition is done.
        bool committed{true};
       // std::vector<book::bookentry> entries{}; ///< in transition.
        using list = std::vector<book::section>;
        book::section& operator *(); ///< Get the reference of this instance.
        book& operator << (book&& r); // move operator, will be removed and replaced with book::bookentry object.
        void remove_last();
        bool is_contents();
        void close();

    };


    static book::section::list sections;
    static book::section::list::iterator current_section;
public:
    static book::section& select(const std::string& section_id);
    static rem::cc init(const std::string& jname, std::function<rem::cc()> inifn = nullptr);
    static bool is_init() { return !book::sections.empty(); }
    static rem::cc append_section(const std::string& section_id);
    static rem::cc end();
    //static rem::cc endl();
    ~book();

    class OBBLIB exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        book::exception operator[](book& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        book *_book_instance_{nullptr};
    };

    book() = default;
    book(rem::type message, rem::cc code, std::source_location src);
    [[nodiscard]] rem::type entry_type() const { return _type_; }
};


}

//#endif //book_H
