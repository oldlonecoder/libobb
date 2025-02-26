//
// Created by oldlonecoder on 14/06/24.
//
//  matricule UPS:
#include <lus/journal.h>


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


namespace lus
{
//std::vector<journal> journal::journals{};
std::mutex journal_guard{};

journal::section::list journal::sections{};
journal::section::list::iterator journal::current_section{};




journal &journal::error(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::err, rem::cc::failed, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::warning(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::warning, rem::cc::ok, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::fatal(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::fatal, rem::cc::failed, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::except(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::except, rem::cc::rejected, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::message(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::message, rem::cc::implemented, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::write(std::source_location src)
{

    journal_guard.lock();
    auto& r = **journal::current_section << journal{};
    r.text << "\r\n";
    journal_guard.unlock();
    return r;
    // journal_guard.lock();
    // if(journal::sections.empty())
    // {
    //     abort();
    //     auto& r = **journal::current_section << journal{rem::type::warning, rem::cc::empty, src};
    //     r << " using uninitialized journal storage -  Initializing with default: 'globals'";
    //     r << "\r\n";
    //     journal_guard.unlock();
    //     return r;
    // }
    //
    // if(!journal::current_section->contents.empty())
    // {
    //     //@todo apply encoded newline : either ascii or html
    //     auto& le = journal::current_section->contents.back();
    //     le.text | "\r\n"; // this way we make sure that we set new line for all oses.
    //     journal_guard.unlock();
    //     return le;
    // }
    // auto& r = **journal::current_section << journal{rem::type::output, rem::cc::empty, src};
    // journal_guard.unlock();
    // return r;
}

journal &journal::debug(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::debug, rem::cc::ok, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::info(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::info, rem::cc::implemented, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::comment(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::comment, rem::cc::implemented, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::syntax(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::syntax, rem::cc::rejected, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::status(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::status, rem::cc::implemented, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::test(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::test, rem::cc::implemented, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::interrupted(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::interrupted, rem::cc::rejected, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}

journal &journal::aborted(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::aborted, rem::cc::rejected, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}


journal &journal::segfault(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::segfault, rem::cc::blocked, src};
    r.init_header();
    journal_guard.unlock();
    return r;
}


journal& journal::jnl(std::source_location src)
{
    journal_guard.lock();
    auto& r = **journal::current_section << journal{rem::type::journal, rem::cc::blocked, src};
    r.init_header();
    journal_guard.unlock();
    return r;

}


journal &journal::operator<<(const std::string &txt)
{
    text << txt;
    return *this;
}

journal &journal::operator<<(const char *txt)
{
    text << txt;
    return *this;
}

journal &journal::operator<<(std::string_view txt)
{
    text << txt;
    return *this;
}

journal &journal::operator<<(const rectangle &r)
{
    text << r.tostring();
    return *this;
}

journal &journal::operator<<(cxy pt)
{
    text << std::format("{},{}", pt.x, pt.y);
    return *this;
}

journal &journal::operator<<(color::code col)
{
    text << col;
    return *this;
}

journal &journal::operator<<(color::pair fgbg)
{
    text << fgbg();
    return *this;
}

journal &journal::operator<<(glyph::type gh)
{
    text << gh;
    return *this;
}

journal &journal::operator<<(rem::type ty)
{
    auto [gh,colors] = rem::type_attributes(ty);
    text << colors << gh  << rem::to_string(ty) << color::reset;
    return *this;
}


journal &journal::operator<<(accent_fr::type ac)
{
    text << accent_fr::data[ac];
    return *this;
}

void journal::init_header()
{
    if(_headercomp_.stamp)
    {
        auto txt{lus::string::now("%H:%M:%S")};
        auto [ic, a] = rem::function_attributes(rem::fn::stamp);
        lus::string acc;
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
        lus::string txt = location.file_name();
        lus::string::word::list words;
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
    // instead, using it explicitly into a distinct journal input
    //------------------------------------------------------------------------------------------------------------
    //    if(headercomp.fun)
    //    {
    //        auto [gh, colors] = journal::functionattributes(rem::fn::fun);
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


journal &journal::operator<<(char ch)
{
    text << ch;
    return *this;
}

void journal::purge(const std::function<void(journal &)>& f)
{
    std::cout << " Purge journal::sections->contents:\n\r";
    for(auto& sec: journal::sections)
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


journal &journal::operator<<(rem::action a_action)
{
    auto [gh,colors] = rem::action_attributes(a_action);
    switch(a_action)
    {
        case rem::action::commit :
        {
            if(!journal::current_section->fout)
                return *this;

            *(journal::current_section->fout) << text() << "\r\n" << std::flush;
            journal::current_section->remove_last();
            return *this;
        }
        break;
        default:
            text << colors() << gh << rem::to_string(a_action);
        break;
    }

    return *this;
}


journal& journal::operator<<(const lus::string::list& _list)
{
    text <<  lus::string::make_str(_list);
    //...
    return *this;
}


journal& journal::operator<<(journal::oef e)
{
    if (journal::current_section->contents.empty()) return *this;
    for (auto& j: journal::current_section->contents)
        j << color::z << rem::action::commit;

    journal::current_section->contents.clear();
    //journal::current_section->contents.back() << color::reset << rem::action::commit;
    return *this;
}


journal& journal::operator<<(const lus::string& _str)
{
    text << _str();
    return *this;
}


journal &journal::operator<<(rem::cc cod)
{
    auto [gh,colors] = rem::return_code_attributes(cod);
    text
        << colors()
        << gh
        << rem::to_string(cod)
        << color::reset << ' ';
    return *this;
}

journal &journal::operator<<(rem::fn fn)
{
    switch (fn) {
        case rem::fn::endl:
            text << '\n';
//            switch (appjournal::format()) ///@todo create journal::format(); directly instead.
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
            //auto txt{lus::string::now("{:%h:%m:%s}", tp)};
            auto [ic, a] = rem::function_attributes(rem::fn::stamp);
            lus::string acc;
            acc << a.fg << glyph::data[ic] <<color::reset << lus::string::now("%H:%M:%S");
            text << acc() << " ";
            return *this;
        }

        case rem::fn::file:
            text << location.file_name();
            return *this;
        case rem::fn::weekday: {
            auto [ic, a] = rem::function_attributes(rem::fn::weekday);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << lus::string::now("%a");
            text << acc();
            return *this;
        }

        case rem::fn::day : {
            auto [ic, a] = rem::function_attributes(rem::fn::day);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << lus::string::now("%d");
            text << acc();
            return *this;
        }

        case rem::fn::month: {
            auto [ic, a] = rem::function_attributes(rem::fn::month);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << lus::string::now("%m");
            text << acc();
            return *this;
        }
        case rem::fn::monthnum: {
            auto [ic, a] = rem::function_attributes(rem::fn::month);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << lus::string::now("%b");
            text << acc();
            return *this;
        }
        case rem::fn::year: {
            auto [ic, a] = rem::function_attributes(rem::fn::year);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc << /*utf::glyph::data[ic] <<*/ a.fg << lus::string::now("%y");
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


journal::exception journal::exception::operator[](journal& el)
{
    _journal_instance_ = &el;
    return *this;
}


journal::journal(rem::type in_type, rem::cc code, std::source_location src):_type_(in_type), _code_(code), location(std::move(src)){text << "\r\n"; }


const char* journal::exception::what() const noexcept
{
    if(_journal_instance_)
    {
        _msg_ = _journal_instance_->text();
        return _msg_.c_str();
    }
    return std::exception::what();
}


journal::section &journal::select(const std::string& section_id)
{
    if(journal::sections.empty())
    {
        // journal::init();
        journal::current_section = journal::sections.begin();
        return journal::sections[0];
    }
    int count=0;
    for(auto& s : journal::sections)
    {
        if(s.id == section_id)
        {
            journal::current_section = journal::sections.begin() + count;
            return s;
        }
        ++count;
    }
    journal::current_section = journal::sections.begin();
    return *journal::current_section;
}



/*!
 * \brief journal::init
 * \param jname
 * \param inifn_ptr
 * \return
 */
rem::cc journal::init(const std::string& jname, std::function<rem::cc()> inifn_ptr)
{
    std::string filename = jname;
    journal::sections.emplace_back(journal::section{.id="globals"});
    journal::current_section = journal::sections.begin();
    if(jname.empty())
        filename = "app";
    journal::current_section->ofs.open(filename+".log", std::ios_base::trunc|std::ios_base::out);
    if(!journal::current_section->ofs.is_open())
        throw "Could not open journal.";

    journal::current_section->fout = &journal::current_section->ofs;
    if(inifn_ptr)
        return inifn_ptr();
    return rem::cc::done;
}



/*!
 * \brief journal::append_section
 * \param section_id
 * \return
 */
rem::cc journal::append_section(const std::string &section_id)
{
    if(journal::select(section_id).id == section_id)
    {
        journal::current_section = journal::sections.begin();
        journal::error() << " section identified by '" << section_id << "' already exists. - request rejected";
        return rem::cc::rejected;
    }
    journal::sections.emplace_back(journal::section{.id=section_id});
    journal::current_section = --journal::sections.end();
    std::string filename{};
    filename = section_id + ".journal";
    journal::current_section->ofs.open(filename.c_str(), std::ios_base::trunc|std::ios_base::out);
    journal::current_section->fout = &journal::current_section->ofs;

    //--journal::current_section;
    return rem::cc::accepted;
}


rem::cc journal::end()
{
    ///@todo Iterate sections and close their output file.
    for(auto& sec : journal::sections)
    {
        sec.ofs.close();
        sec.contents.clear();
    }

    ///...
    //journal::current_section->close();
    return rem::cc::done;
}



/*!
 * \brief journal::~journal
 *  Flushes any un-commited queued section contents marking it as commited.
 *
 *  @note Not yet used as the location of journal instances are stored into the section containers
 *        For future re-design.
 */
journal::~journal()
{
//    if(journal::current_section->is_contents())
//        journal::current_section->contents.back() << color::reset << rem::action::commit;

}

journal::section &journal::section::operator*()
{
    return *this;
}

journal &journal::section::operator<<(journal &&r)
{
    contents.emplace_back(r);
    return contents.back();
}


void journal::section::remove_last()
{
    if(!contents.empty())
        contents.pop_back();
    committed=true;
}

bool journal::section::is_contents() { return !committed; }


void journal::section::close()
{
    journal::info() << rem::fn::func << " " << rem::fn::month << "," << rem::fn::year << " " << rem::fn::hour << ":"  << rem::fn::minute << ":" << rem::fn::seconds << rem::action::end;
    if(ofs.is_open()) ofs.close();
    committed=true;
}
} // namespace oom
