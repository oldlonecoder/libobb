//
// Created by oldlonecoder on 14/06/24.
//
//  matricule UPS:
#include <obb/logbook.h>


/******************************************************************************************
 *   Copyright (C) ...,2024,... by luxe luxsier                                          *
 *   luxe.luxsier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (luxe luxsier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than luxe luxsier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (luxe luxsier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/


//#pragma once
namespace Fs = std::filesystem;


namespace obb
{
//std::vector<book> book::books{};
std::mutex book_guard{};

book::section::list book::sections{};
book::section::list::iterator book::current_section{};


std::map<rem::type, bool> book::_use_types{
    {rem::type::err,true},
    {rem::type::warning,true},
    {rem::type::fatal,true},
    {rem::type::except,true},
    {rem::type::message,true},
    {rem::type::output,true},
    {rem::type::debug,true},
    {rem::type::info,true},
    {rem::type::comment,true},
    {rem::type::syntax,true},
    {rem::type::status,true},
    {rem::type::test,true},
    {rem::type::interrupted,true},
    {rem::type::aborted,true},
    {rem::type::segfault,true},
    {rem::type::book,true}
};

static bool ENABLED_ERROR       = true;
static bool ENABLED_WARNING     = true;
static bool ENABLED_FATAL       = true;
static bool ENABLED_EXCEPT      = true;
static bool ENABLED_MESSAGE     = true;
static bool ENABLED_OUTPUT      = true;
static bool ENABLED_DEBUG       = true;
static bool ENABLED_INFO        = true;
static bool ENABLED_COMMENT     = true;
static bool ENABLED_SYNTAX      = true;
static bool ENABLED_STATUS      = true;
static bool ENABLED_TEST        = true;
static bool ENABLED_INTERRUPTED = true;
static bool ENABLED_ABORTED     = true;
static bool ENABLED_SEGFAULT    = true;
static bool ENABLED_BOOK        = true;


book &book::error(std::source_location src)
{
    if(!ENABLED_ERROR) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::err, rem::cc::failed, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::warning(std::source_location src)
{
    if(!ENABLED_WARNING) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::warning, rem::cc::ok, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::fatal(std::source_location src)
{
    if(!ENABLED_FATAL ) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::fatal, rem::cc::failed, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::except(std::source_location src)
{
    if(!ENABLED_EXCEPT) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::except, rem::cc::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::message(std::source_location src)
{
    if(!ENABLED_MESSAGE) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::message, rem::cc::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::write(std::source_location src)
{
    if(!ENABLED_OUTPUT) return book::current_section->contents.back();

    book_guard.lock();
    auto& r = **book::current_section << book{};
    r.text << "\r\n";
    book_guard.unlock();
    return r;
    // book_guard.lock();
    // if(book::sections.empty())
    // {
    //     abort();
    //     auto& r = **book::current_section << book{rem::type::warning, rem::cc::empty, src};
    //     r << " using uninitialized book storage -  Initializing with default: 'globals'";
    //     r << "\r\n";
    //     book_guard.unlock();
    //     return r;
    // }
    //
    // if(!book::current_section->contents.empty())
    // {
    //     //@todo apply encoded newline : either ascii or html
    //     auto& le = book::current_section->contents.back();
    //     le.text | "\r\n"; // this way we make sure that we set new line for all oses.
    //     book_guard.unlock();
    //     return le;
    // }
    // auto& r = **book::current_section << book{rem::type::output, rem::cc::empty, src};
    // book_guard.unlock();
    // return r;
}

book &book::debug(std::source_location src)
{
    if(!ENABLED_DEBUG) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::debug, rem::cc::ok, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::info(std::source_location src)
{
    if(!ENABLED_INFO) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::info, rem::cc::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::comment(std::source_location src)
{
    if(!ENABLED_COMMENT) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::comment, rem::cc::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::syntax(std::source_location src)
{
    if(!ENABLED_SYNTAX) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::syntax, rem::cc::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::status(std::source_location src)
{
    if(!ENABLED_STATUS) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::status, rem::cc::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::test(std::source_location src)
{
    if(!ENABLED_TEST) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::test, rem::cc::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::interrupted(std::source_location src)
{
    if(!ENABLED_INTERRUPTED) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::interrupted, rem::cc::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::aborted(std::source_location src)
{
    if(!ENABLED_ABORTED) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::aborted, rem::cc::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}


book &book::segfault(std::source_location src)
{
    if(!ENABLED_SEGFAULT) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::segfault, rem::cc::blocked, src};
    r.init_header();
    book_guard.unlock();
    return r;
}


book& book::jnl(std::source_location src)
{
    if(!ENABLED_BOOK) return book::current_section->contents.back();
    book_guard.lock();
    auto& r = **book::current_section << book{rem::type::book, rem::cc::blocked, src};
    r.init_header();
    book_guard.unlock();
    return r;

}


book &book::operator<<(const std::string &txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(const char *txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(std::string_view txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(const rectangle &r)
{
    text << r.tostring();
    return *this;
}

book &book::operator<<(cxy pt)
{
    text << std::format("{},{}", pt.x, pt.y);
    return *this;
}

book &book::operator<<(color::code col)
{
    text << col;
    return *this;
}

book &book::operator<<(color::pair fgbg)
{
    text << fgbg();
    return *this;
}

book &book::operator<<(glyph::type gh)
{
    text << gh;
    return *this;
}

book &book::operator<<(rem::type ty)
{
    auto [gh,colors] = rem::type_attributes(ty);
    text << colors << gh  << rem::to_string(ty) << color::reset;
    return *this;
}


book &book::operator<<(accent_fr::type ac)
{
    text << accent_fr::data[ac];
    return *this;
}

void book::init_header()
{
    if(_headercomp_.stamp)
    {
        auto txt{obb::string::now("%H:%M:%S")};
        auto [ic, a] = rem::function_attributes(rem::fn::stamp);
        obb::string acc;
        acc << a.fg << glyph::data[ic]  << txt;
        text << acc() << " ";
    }
    if(_headercomp_.type)
    {
        auto [gh,colors] = rem::type_attributes(_type_);
        text << colors << gh  << ' ' << rem::to_string(_type_) << color::reset << ' ';
    }

    if(_headercomp_.file)
    {
        auto [gh, colors] = rem::function_attributes(rem::fn::file);
        obb::string txt = location.file_name();
        obb::string::word::list words;
        if(auto count = txt.words(words, false, "/"); !count) return ;
        text << color::reset << " in " << colors << gh;
        if(words.size() > 1)
        {
            auto i = words.end();
            --i; // filename
            auto filename = *i;
            --i; // parent dir
            text << **i;
            ++i;
            text << '/' << **i << ' ';
        }
        words.clear();
    }
    // disable uncontrollable and potentially insane length of function signature given by std::source_location.
    // instead, using it explicitly into a distinct book input
    //------------------------------------------------------------------------------------------------------------
    //    if(headercomp.fun)
    //    {
    //        auto [gh, colors] = book::functionattributes(rem::fn::fun);
    //        text << colors << gh << ' ' << location.function_name() << color::reset;
    //    }
    //------------------------------------------------------------------------------------------------------------
    if(_headercomp_.line)
    {
        auto [gh, colors] = rem::function_attributes(rem::fn::line);
        text << colors << "line: " << std::format("{}", location.line()) << color::reset;
    }
    if(_headercomp_.fun)
        (*this) << rem::fn::endl << rem::fn::func;

    //text << " \r\n";
}


book &book::operator<<(char ch)
{
    text << ch;
    return *this;
}

void book::purge(const std::function<void(book &)>& f)
{
    std::cout << " Purge book::sections->contents:\n\r";
    for(auto& sec: book::sections)
    {
        std::cout << " Section: [" << sec.id << "]:\n\r--------------------------------------------------------\n\r";
        for(auto& r : sec.contents)
        {
            if (f)
                f(r);
            else
                std::cout << r.text() << "\r\n";

            r.text.clear();
        }
        sec.contents.clear();
    }
}


book &book::operator<<(rem::action a_action)
{
    auto [gh,colors] = rem::action_attributes(a_action);
    switch(a_action)
    {
        case rem::action::commit :
        {
            if(!book::current_section->fout)
                return *this;

            *(book::current_section->fout) << text() << "\r\n" << std::flush;
            book::current_section->remove_last();
            return *this;
        }
        break;
        default:
            text << colors() << gh << rem::to_string(a_action);
        break;
    }

    return *this;
}


book& book::operator<<(const obb::string::list& _list)
{
    text <<  obb::string::make_str(_list);
    //...
    return *this;
}


book& book::operator<<(book::oef e)
{
    if (book::current_section->contents.empty()) return *this;
    for (auto& j: book::current_section->contents)
        j << color::z << rem::action::commit;

    book::current_section->contents.clear();
    //book::current_section->contents.back() << color::reset << rem::action::commit;
    return *this;
}


book& book::operator<<(const obb::string& _str)
{
    text << _str();
    return *this;
}


book &book::operator<<(rem::cc cod)
{
    auto [gh,colors] = rem::return_code_attributes(cod);
    text
        << colors()
        << gh
        << rem::to_string(cod)
        << color::reset << ' ';
    return *this;
}

book &book::operator<<(rem::fn fn)
{
    switch (fn) {
        case rem::fn::endl:
            text << '\n';
//            switch (appbook::format()) ///@todo create book::format(); directly instead.
//            {
//                case color::format::ansi256:
//                    input("\n");
//                    break;
//                case color::format::html:
//                    input("<br />");
//                    break;
//            }
            break;
        case rem::fn::stamp: {
            /*
                 * %d %f ou %d %m %y
                 * %r %t %h %m %s
                 * %a {monday} %a {mon}
                 * %b {june}   %b {jun}
            */


            //std::chrono::zoned_time date{"america/toronto", std::chrono::system_clock::now()};
            //const auto tp{std::chrono::system_clock::now()};
            //auto txt{obb::string::now("{:%h:%m:%s}", tp)};
            auto [ic, a] = rem::function_attributes(rem::fn::stamp);
            obb::string acc;
            acc << a.fg << glyph::data[ic] <<color::reset << obb::string::now("%H:%M:%S");
            text << acc() << " ";
            return *this;
        }

        case rem::fn::file:
            text << location.file_name();
            return *this;
        case rem::fn::weekday: {
            auto [ic, a] = rem::function_attributes(rem::fn::weekday);
            //auto today{std::chrono::system_clock::now()};
            obb::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << obb::string::now("%a");
            text << acc();
            return *this;
        }

        case rem::fn::day : {
            auto [ic, a] = rem::function_attributes(rem::fn::day);
            //auto today{std::chrono::system_clock::now()};
            obb::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << obb::string::now("%d");
            text << acc();
            return *this;
        }

        case rem::fn::month: {
            auto [ic, a] = rem::function_attributes(rem::fn::month);
            //auto today{std::chrono::system_clock::now()};
            obb::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << obb::string::now("%m");
            text << acc();
            return *this;
        }
        case rem::fn::monthnum: {
            auto [ic, a] = rem::function_attributes(rem::fn::month);
            //auto today{std::chrono::system_clock::now()};
            obb::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << obb::string::now("%b");
            text << acc();
            return *this;
        }
        case rem::fn::year: {
            auto [ic, a] = rem::function_attributes(rem::fn::year);
            //auto today{std::chrono::system_clock::now()};
            obb::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << obb::string::now("%y");
            text <<acc();
            return *this;
        }
        case rem::fn::func:
            auto [gh, colors] = rem::function_attributes(rem::fn::func);
            text << "From " << colors << location.function_name() << color::reset << "\n";
            break;

        //default: break;
    }
    return *this;
}


book::exception book::exception::operator[](book& el)
{
    _book_instance_ = &el;
    return *this;
}


book::book(rem::type in_type, rem::cc code, std::source_location src):_type_(in_type), _code_(code), location(std::move(src)){text << "\r\n"; }


const char* book::exception::what() const noexcept
{
    if(_book_instance_)
    {
        _msg_ = _book_instance_->text();
        return _msg_.c_str();
    }
    return std::exception::what();
}


book::section &book::select(const std::string& section_id)
{
    if(book::sections.empty())
    {
        // book::init();
        book::current_section = book::sections.begin();
        return book::sections[0];
    }
    int count=0;
    for(auto& s : book::sections)
    {
        if(s.id == section_id)
        {
            book::current_section = book::sections.begin() + count;
            return s;
        }
        ++count;
    }
    book::current_section = book::sections.begin();
    return *book::current_section;
}



/*!
 * \brief book::init
 * \param jname
 * \param inifn_ptr
 * \return
 */
rem::cc book::init(const std::string& jname, std::function<rem::cc()> inifn_ptr)
{
    std::string filename = jname;
    book::sections.emplace_back(book::section{.id="globals"});
    book::current_section = book::sections.begin();
    if(jname.empty())
        filename = "app";
    book::current_section->ofs.open(filename+".log", std::ios_base::trunc|std::ios_base::out);
    if(!book::current_section->ofs.is_open())
        throw "Could not open book.";

    book::current_section->fout = &book::current_section->ofs;
    if(inifn_ptr)
        return inifn_ptr();
    return rem::cc::done;
}



/*!
 * \brief book::append_section
 * \param section_id
 * \return
 */
rem::cc book::append_section(const std::string &section_id)
{
    if(book::select(section_id).id == section_id)
    {
        book::current_section = book::sections.begin();
        book::error() << " section identified by '" << section_id << "' already exists. - request rejected";
        return rem::cc::rejected;
    }
    book::sections.emplace_back(book::section{.id=section_id});
    book::current_section = --book::sections.end();
    std::string filename{};
    filename = section_id + ".book";
    book::current_section->ofs.open(filename.c_str(), std::ios_base::trunc|std::ios_base::out);
    book::current_section->fout = &book::current_section->ofs;

    //--book::current_section;
    return rem::cc::accepted;
}


rem::cc book::end()
{
    ///@todo Iterate sections and close their output file.
    for(auto& sec : book::sections)
    {
        sec.ofs.close();
        sec.contents.clear();
    }

    ///...
    //book::current_section->close();
    return rem::cc::done;
}



/*!
 * \brief book::~book
 *  Flushes any un-commited queued section contents marking it as commited.
 *
 *  @note Not yet used as the location of book instances are stored into the section containers
 *        For future re-design.
 */
book::~book()
{
//    if(book::current_section->is_contents())
//        book::current_section->contents.back() << color::reset << rem::action::commit;

}

book::section &book::section::operator*()
{
    return *this;
}

book &book::section::operator<<(book &&r)
{
    contents.emplace_back(r);
    return contents.back();
}


void book::section::remove_last()
{
    if(!contents.empty())
        contents.pop_back();
    committed=true;
}

bool book::section::is_contents() { return !committed; }


void book::section::close()
{
    book::info() << rem::fn::func << " " << rem::fn::month << "," << rem::fn::year << " " << rem::fn::hour << ":"  << rem::fn::minute << ":" << rem::fn::seconds << rem::action::end;
    if(ofs.is_open()) ofs.close();
    committed=true;
}
} // namespace oom
