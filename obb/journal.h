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

#include <lus/glyphes.h>
#include <lus/string.h>

#include <source_location>

#include <functional>
#include <lus/geometry.h>
#include <filesystem>
#include <fstream>



using lus::ui::color;
using lus::glyph;
using lus::accent_fr;
using lus::ui::rectangle;
using lus::ui::cxy;
using lus::ui::size;






namespace lus
{

class object;

class LUSLIB journal
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
    lus::string  text{};

    header_component _headercomp_{1,0,1,1,1,1};
public:


    enum oef : integers::u8 { eol,endl };
    static journal& error       (std::source_location src = std::source_location::current());
    static journal& warning     (std::source_location src = std::source_location::current());
    static journal& fatal       (std::source_location src = std::source_location::current());
    static journal& except      (std::source_location src = std::source_location::current());
    static journal& message     (std::source_location src = std::source_location::current());
    static journal& write       (std::source_location src = std::source_location::current());
    static journal& debug       (std::source_location src = std::source_location::current());
    static journal& info        (std::source_location src = std::source_location::current());
    static journal& comment     (std::source_location src = std::source_location::current());
    static journal& syntax      (std::source_location src = std::source_location::current());
    static journal& status      (std::source_location src = std::source_location::current());
    static journal& test        (std::source_location src = std::source_location::current());
    static journal& interrupted (std::source_location src = std::source_location::current());
    static journal& aborted     (std::source_location src = std::source_location::current());
    static journal& segfault    (std::source_location src = std::source_location::current());
    static journal& jnl         (std::source_location src = std::source_location::current());

    journal& operator << (const std::string& txt);
    journal& operator << (const char* txt);
    journal& operator << (char ch);
    journal& operator << (std::string_view txt);
    journal& operator << (const rectangle& r);
    journal& operator << (ui::cxy pt);
    journal& operator << (color::code col);
    journal& operator << (color::pair fgbg);
    journal& operator << (glyph::type gh);
    journal& operator << (accent_fr::type ac);
    journal& operator << (rem::type ty);
    journal& operator << (rem::cc cod);
    journal& operator << (rem::fn fn);
    journal& operator << (rem::action a_action);
    journal& operator << (const lus::string::list& _list );
    journal& operator << (journal::oef e);
    journal& operator << (const lus::string& str );
    template<typename T> journal& operator << (const T& v)
    {
        text << v;
        return *this;
    }

    static std::vector<journal> _mem_stream_;
    void init_header();
    static void purge(const std::function<void(journal &)>& f);

    struct LUSLIB section
    {
        std::string id;   ///< Section ID which is also the base name of the output file.
        std::ofstream ofs;
        std::ofstream* fout{nullptr}; ///< will see.
        std::vector<journal> contents{}; ///< Actual contents. Will be transferred into the entries container when the transition is done.
        bool committed{true};
       // std::vector<journal::journalentry> entries{}; ///< in transition.
        using list = std::vector<journal::section>;
        journal::section& operator *(); ///< Get the reference of this instance.
        journal& operator << (journal&& r); // move operator, will be removed and replaced with journal::journalentry object.
        void remove_last();
        bool is_contents();
        void close();

    };


    static journal::section::list sections;
    static journal::section::list::iterator current_section;
public:
    static journal::section& select(const std::string& section_id);
    static rem::cc init(const std::string& jname, std::function<rem::cc()> inifn = nullptr);
    static bool is_init() { return !journal::sections.empty(); }
    static rem::cc append_section(const std::string& section_id);
    static rem::cc end();
    //static rem::cc endl();
    ~journal();

    class LUSLIB exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        journal::exception operator[](journal& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        journal *_journal_instance_{nullptr};
    };

    journal() = default;
    journal(rem::type message, rem::cc code, std::source_location src);
    [[nodiscard]] rem::type entry_type() const { return _type_; }
};


}

//#endif //journal_H
