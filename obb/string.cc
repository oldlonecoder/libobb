//
// Created by oldlonecoder on 8/21/24.
//



/******************************************************************************************
 *   Copyright (C) ...,2024,... by luxe Lussier                                          *
 *   luxe.lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (luxe Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than luxe Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (luxe Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/

//#pragma once


#include <lus/string.h>

#define out std::cout
#define lend std::endl;

namespace lus
{


#define num_constructor(v) { std::ostringstream os; os << (v); _d_ = os.str(); }
#define num_assign(v) { std::ostringstream os; os << (v); _d_ += os.str(); return *this; }


string::string(const std::string& a_str)
{
    _d_ = a_str;
}


string::string(const char* a_str): _d_(a_str){}


string::string(const string& a_str):_d_(a_str._d_){}
string::string(char a_ch)num_constructor(a_ch)


string::string(integers::u8 v)  num_constructor(v)
string::string(integers::u16 v) num_constructor(v)
string::string(integers::u32 v) num_constructor(v)
string::string(integers::u64 v) num_constructor(v)
string::string(integers::i8 v)  num_constructor(v)
string::string(integers::i16 v) num_constructor(v)
string::string(integers::i32 v) num_constructor(v)
string::string(integers::i64 v) num_constructor(v)
string::string(float v)         num_constructor(v)


string::~string()
{
    _d_.clear();
}


string& string::operator=(const string& a_str) { _d_ = a_str._d_; return *this; }
string& string::operator=(const char* a_str)   { _d_ = a_str; return *this; }
string& string::operator=(char a_ch)           { _d_ = a_ch; return *this; }
string& string::operator=(integers::u8 v)      num_assign(v)
string& string::operator=(integers::u16 v)     num_assign(v)
string& string::operator=(integers::u32 v)     num_assign(v)
string& string::operator=(integers::u64 v)     num_assign(v)
string& string::operator=(integers::i8 v)      num_assign(v)
string& string::operator=(integers::i16 v)     num_assign(v)
string& string::operator=(integers::i32 v)     num_assign(v)
string& string::operator=(integers::i64 v)     num_assign(v)
string& string::operator=(const std::string& a_str) { _d_ = a_str; return *this; }
string& string::operator=(float v)             num_assign(v)
string& string::operator=(double v)            num_assign(v)


string& string::operator << (color::code color)
{
    _d_ += color::render(color);
    return *this;
}


string& string::operator << (color::pair colors)
{
    _d_ += color::render(colors);
    return *this;
}


string& string::operator << (glyph::type ig)
{
    if(ig > glyph::journal) return *this;
    _d_ += glyph::data[ig];
    return *this;
}


string& string::operator << (accent_fr::type ac)
{
    _d_ += accent_fr::data[ac];
    return *this;
}


string& string::operator << (cadre::index fri)
{
    _d_ += cadre()[fri];
    return *this;
}


std::string string::word::operator*()
{
    return {begin, last+1};
}



/*!
 * \brief string::words
 * \param a_list
 * \param a_keep_as_word
 * \param a_sep
 * \return
 * \note The code below is very hard to read, I know, even from myself being the author... I had to choose between speed + efficiency + weight - and readability. I have chosen speed...
 */
size_t string::words(string::word::list& a_list, bool a_keep_as_word, const char* a_sep)
{
    if(_d_.empty()) return 0;
    //out << __PRETTY_FUNCTION__ << std::endl << " text: '" << _d_ << "'" << std::endl;
    string::word w{_d_.begin(),_d_.begin(), 0};
    if(!a_sep) a_sep = string::s_default_separators;
    //out << "separators : '" << color::render(color::yellow) << a_sep << color::render(color::reset) << "'" << std::endl;
    //out << "init the first word with: '" << *w << '\'' << lend;
    if(_d_.size() < 2) return 1;
    //...
    do
    {
        // out << "start iteration, w :'" << *w << '\'' << lend;
        // out << "w.last '" << *w.last << '\'' << lend;
        // out << " check separators: at '" << *w.last << '\''  << std::endl;
        if(std::string(a_sep).find(*w.last, 0/* DUH!!!!!!!!!!!!!!!!!!!*/) != std::string::npos)
        {
            if(w.last > w.begin)
            {
                a_list.push_back({w.begin, w.last-1, w.begin-_d_.begin()});
                // out << "push verify word before separator: '" << *a_list.back() << "'" << std::endl;
                w.sync(_d_);
            }
            if(a_keep_as_word)
            {
                a_list.push_back({w.begin, w.last, w.begin-_d_.begin()});
                // out << "push separator as word: '" << *a_list.back() << '\'' << lend;
                w.sync(_d_); //!!
                // out << "> push separator as word: sync'ed w:'" << *w << '\'' << lend;
            }
            if(!eat(w))
            {
                // out << "in separator journalic: eat reached end of string. - break;" << std::endl;
                break;
            }
            w.sync(_d_);
            continue;
        }
        // out << "check white spaces :" << std::endl;
        if(std::isspace(*w.last))
        {
            // out << " in white spaces ..." << std::endl;
            if(w.last > w.begin)
            {
                a_list.push_back({w.begin,w.last-1, w.begin-_d_.begin()});
                // out << "push before whitespace: '" << *a_list.back() << '\'' << lend;
                if(!eat(w)) break;
            }
            while(std::isspace(*w.last) && w.last != _d_.end()) ++w.last;
            if(w.last == _d_.end()) break;

            w.sync(_d_);
            continue;
        }
        // out << "check quotes : " << std::endl;
        if(*w.last == '"' || *w.last == '\'')
        {
            auto c = *w.last;
            if(!eat(w)) break; // advance w.last ...
            if(auto off = _d_.find(c, w.last-_d_.begin()) != std::string::npos)
            {
                if(a_keep_as_word)
                {
                    a_list.push_back({w.begin,w.begin,w.offset});

                    ++w.begin;
                    ++w.offset;
                }
                w.last = _d_.begin()+off;
                // w.last now on the second quote, closing the string.
                // Push "string" content.
                a_list.push_back({w.begin,w.last-1,w.begin-_d_.begin()});
                // out << "push : '" << *a_list.back() << '\'' << lend;
                w.sync(_d_);
                if(a_keep_as_word)
                {
                    a_list.push_back({w.begin,w.begin,w.offset});
                    // out << "push : '" << *a_list.back() << '\'' << lend;
                    ++w.begin;
                    ++w.offset;
                }

                if(!eat(w)) break;
                w.sync(_d_);
                continue;
            }
            // else
            // {
            //     // unterminated enclosed string : " blah <=> 'halb ...";
            //     a_list.push_back({w.begin,w.last,w.begin-_d_.begin()});
            //     out << "push : '" << *a_list.back() << '\'' << lend;
            //     break;
            // }
        }
        if(!eat(w)) break;

    }while(w.last != _d_.end());
    if(w.last > w.begin)
    {
        a_list.push_back({w.begin,w.last, w.begin-_d_.begin()});
        // out << "push last word ( w.last > w.begin ) :' " << *a_list.back() << '\'' << lend;
    }

    return a_list.size();
}


bool string::eat(string::word& w)
{
    if(w.last == _d_.end()) return false;
    ++w.last;
    if(w.last == _d_.end())
    {
        --w.last;
        return false;
    }
    return true;
}


std::string string::make_str(const lus::string::list& _list)
{
    std::string str="{";
    int col=0;
    for (auto const& c:_list)
    {
        if (col++)
            str += ',';
        str += c;
    }
    str += '}';
    return str;
}




std::string string::now(const std::string& str_fmt)
{
    // Old archaic Code...
    // time_t rawtime;
    // struct tm* timeinfo;
    // char tmb[180];
    // std::time(&rawtime);
    // timeinfo = std::localtime(&rawtime);
    // std::strftime(tmb, 60, str_fmt.c_str(), timeinfo);
    // std::string _s = tmb;
    // //return tmb;


    auto current = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::to_time_t(current);
    auto local = localtime(&now);
    std::ostringstream ostr;
    ostr << std::put_time(local, str_fmt.c_str());
    return ostr.str();
}

std::string string::bytes(std::string_view a_seq)
{
    std::string outstr{};

    int c = 0;
    for(auto ch  : a_seq)
    {
        outstr += std::format("0x{:02x}", static_cast<int>(ch));
        if(c++ < (a_seq.size()-1)) outstr += ',';
    }

    return outstr;
}

std::string string::bytes(std::vector<int> a_seq)
{
    std::string outstr{};
    int c = 0;
    for(auto n  : a_seq)
    {
        outstr += std::format("{:02x}/{:d}", n,n);
        if(c++ < (a_seq.size()-1)) outstr += ',';
    }

    return outstr;
}



std::vector<std::string_view> string::string_view_list(int Count, char** s, int offset)
{
    std::vector<std::string_view> result;
    if (offset == Count) return {};
    for(int i = offset; i < Count; ++i) result.emplace_back(s[i]);
    return result;
}


lus::string::list string::make_list(int argc, char** argv, int offset)
{
    std::vector<std::string> result;
    for(int i = offset; i < argc; ++i) result.emplace_back(argv[i]);
    return result;
}
} // lux
