/******************************************************************************************
*   Copyright (C) ...,2024,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/


#include <lus/est/alu.h>

using namespace lus::integers;

namespace lus::est
{

std::string  alu::mNil;
#define debug_out ;
//journal::debug() << rem::fn::fun << "rhs=" << rhs << ", this = " << v.d << " : types: " << lexer_component::type_name(T);


alu::alu(int8_t rhs) : T(lex::type::I8|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(int16_t rhs) : T(lex::type::I16|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(int32_t rhs) : T(lex::type::I32|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(int64_t rhs) : T(lex::type::I64|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(uint8_t rhs) : T(lex::type::U8|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(uint16_t rhs) : T(lex::type::U16|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(uint32_t rhs) : T(lex::type::U32|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(uint64_t rhs) : T(lex::type::U64|lex::type::Number|lex::type::Leaf)
{ v.d = rhs; debug_out}
alu::alu(bool rhs) : T(lex::type::Bool)
{v.d = rhs; debug_out}

#define cast(rhs)\
(rhs).T & lex::type::Bool  ? (rhs).v.d != false :\
(rhs).T & lex::type::I8       ? (rhs).v.d:\
(rhs).T & lex::type::I16      ? (rhs).v.d:\
(rhs).T & lex::type::I32      ? (rhs).v.d:\
(rhs).T & lex::type::I64      ? (rhs).v.d:\
(rhs).T & lex::type::U8       ? (rhs).v.d:\
(rhs).T & lex::type::U16      ? (rhs).v.d:\
(rhs).T & lex::type::U32      ? (rhs).v.d:\
(rhs).T & lex::type::U64      ? (rhs).v.d:\
(rhs).T & lex::type::Float    ? (rhs).v.d :0




alu::alu(double rhs)
{
    T = lex::type::Number | lex::type::Float | lex::type::Leaf;
    v.d = rhs;
}

alu::alu() {}

alu::alu(float rhs)
{
    T = lex::type::Number | lex::type::Float | lex::type::Leaf;
    v.d = (double)rhs;
}

alu::alu(const std::string& rhs)
{
    T = lex::type::Text | lex::type::Leaf;
    v.t = &text; text = rhs;
}

alu::alu(const char* rhs)
{

    T = lex::type::Text | lex::type::Leaf;
    v.t = &text; text = rhs;
}

alu::alu(void* rhs)
{
    T = lex::type::Any | lex::type::VoidPtr;
    v.p = rhs;
}

bool alu::type_size(const alu& Rhs_) const
{
    lex::type::T me = T & (lex::type::I8 | lex::type::I16 | lex::type::I32 | lex::type::I64 | lex::type::U8 | lex::type::U16 | lex::type::U32 | lex::type::U64 | lex::type::Float);
    lex::type::T r = Rhs_.T & (lex::type::I8 | lex::type::I16 | lex::type::I32 | lex::type::I64 | lex::type::U8 | lex::type::U16 | lex::type::U32 | lex::type::U64 |lex::type:: Float);
    return static_cast<U64>(me) - static_cast<U64>(r) >= 0;
}

alu::operator bool() const
{
    if (!static_cast<U64>(v.d) || !static_cast<U64>(v.d))
        return false;
    if (!T)
        return false;
    if (T & lex::type::Text)
        return !text.empty();
    if (T & lex::type::Number)
        return v.d != 0.0f;
    if (T & lex::type::VoidPtr)
        return value<void *>() != nullptr;
    return false;
}

//#define lr_number(rhs) if ((T&lex::type::Number) && ((rhs).T&lex::type::Number))
#define lr_number(rhs) if (T&lex::type::Number&(rhs).T)
#define lrtext(rhs)   if ((T&lex::type::Text) && ((rhs).T&lex::type::Text))
#define lr_any(rhs)    if ((T&lex::type::Any)  && ((rhs).T&lex::type::Any))
#define is_integrale(rhs) if (!((rhs).T&lex::type::Float))
#define istext(i)    if((i).T & lex::type::Text)
#define is_number if ((T&(lex::type::Float|lex::type::Number)))
// #define delstring_if(rhs) if ((T&lex::type::Text) && (!(rhs).T & lex::type::Text)) delete v..t;  Vieux stuff

alu& alu::operator=(const alu& rhs)
{
    debug_out
    if (&rhs != this)
    {
        T = rhs.T;
        v = rhs.v;
        return *this; // WTF???????
    }

    if (T & lex::type::Text)
    {
        text = rhs.text;
        return *this;
    }
    if (T & lex::type::Any)
    {
        v.p = rhs.v.p;
        return *this;
    }
    *this = false;
    return *this;
}


alu alu::operator+(const alu& rhs) const
{
    lrtext(rhs)
        return {text + rhs.text};
    else lr_number(rhs)
        return {v.d + rhs.v.d}; // Slow?

    throw journal::exception()[ journal::except() <<" [" << lexer_component::type_name(T) << "] and [" << lexer_component::type_name(rhs.T) << "] are incompatible."] ;
    return {false};
}


alu alu::operator==(const alu & lf) const
{
    alu a;
    lrtext(lf)
    {
        a = lf.text == text;
        return a;
    }
    lr_number(lf)
    {
        return lf.number<double>() == number<double>();
    }
    throw journal::exception()[ journal::except() <<" Equality comparison between different types(" << lexer_component::type_name(T) << " == " << lexer_component::type_name(lf.T) << ')'] ;
    return {false};
}

alu alu::operator[](alu::CNV c)
{
    istext(*this)
    {
        return {0.0f};
    }
    auto d = v.d;

    alu    a;
    switch (c)
    {
        case alu::DEG:
            a = d * 180.0f / 3.141592653589793;
            break;
        case alu::RAD:
            a = d * 3.141592653589793 / 180.0f;
            break;
        default:
            a = 0.0f;
            break;
    }
    return a;
}

alu alu::operator-(const alu& rhs)
{
    //journal::debug() << rem::fn::fun << " rhs=" << rhs.to_str();
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<" substraction operator strings is not yet supported"] ;
        //return remove_substr_copy(rhs.text);
        return *this;
    }

    lr_number(rhs)
        return {v.d - rhs.v.d};
    lr_any(rhs)
        return {reinterpret_cast<uint64_t>(value<void *>()) - reinterpret_cast<uint64_t>(rhs.value<void *>())};

    throw journal::exception()[ journal::except() <<"cannot apply sign on " << lexer_component::type_name(T)] ;
    return {false};
}


alu alu::operator*(const alu& rhs) const
{
    alu f;
    lrtext(rhs)
    {
        std::size_t pos = rhs.text.find(text);
        return {pos != std::string::npos};
    }

    //else
    lr_number(rhs)
        return {v.d * rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot multiply" << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return {};
}

alu alu::operator/(const alu& rhs)
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot divide strings"] ;
        return {};
    }
    //    f = text + rhs.text;
    //else
    lr_number(rhs)
    {
        double vr = rhs.v.d;
        double lr = v.d;

        if (vr == 0.0L)
        {
            throw journal::exception()[ journal::except() << rem::type::err  << " alu operation: " << rem::cc::divbyzero << " =>(" << (*this)() << " / " << rhs() << ")" ];
            return "Inf";
        }
        return {lr / vr};
    }

    throw journal::exception()[ journal::except() <<"cannot divide " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return {};
}

alu alu::operator%(const alu& rhs) const
{
    alu f;
    lrtext(rhs)
    {
        throw  journal::exception()[ journal::except() <<"cannot modulo strings"];
        return {};
    }
    lr_number(rhs)
        return {static_cast<U64>(v.d) % static_cast<U64>(rhs.v.d)};

    throw journal::exception()[ journal::except() <<"cannot modulo " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."] ;
    return {};
}

alu alu::operator^(const alu& rhs) const
{
    alu f;
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot xor strings"];
        return {};
    }

    lr_number(rhs)
        return {static_cast<U64>(v.d) ^ static_cast<U64>(rhs.v.d)};

    throw journal::exception()[ journal::except() <<"cannot xor " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return {};
}

alu alu::operator<<(const alu& rhs) const
{
    alu f;
    lrtext(rhs)
    {
        lus::string str = text;
        str << rhs.text;
        return {str()};
    }

    lr_number(rhs)
        return {static_cast<U64>(v.d)<< static_cast<U64>(rhs.v.d)};

    throw journal::exception()[ journal::except() <<"cannot execute bitwise left-shift or insert with " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return f;
}
alu alu::operator>>(const alu& rhs) const
{
    alu f;
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute bitwise right-shift or extract/write/send string on string " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    }
    lr_number(rhs)
        return {static_cast<U64>(v.d) >> static_cast<U64>(rhs.v.d)};


    throw journal::exception()[ journal::except() <<"cannot execute bitwise right-shift or extract/write/send with " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."] ;
    return f;
}

alu alu::operator|(const alu& rhs) const
{

    lrtext(rhs)
    {
        return {text + rhs.text};
    }
    lr_number(rhs)
        return {static_cast<U64>(v.d) | static_cast<U64>(rhs.v.d)};

    throw journal::exception()[ journal::except() <<"cannot execute bitwise or with " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return {};
}

alu alu::operator&(const alu& rhs) const
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute bitwise and on string "];
    }
    lr_number(rhs)
        return {static_cast<U64>(v.d) & static_cast<U64>(rhs.v.d)};

    throw journal::exception()[ journal::except() <<"cannot execute bitwise and between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return {};
}

alu alu::operator~()
{
    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot execute bitwise invert on string " ];
    }

    is_number
    {
        if (T & lex::type::Float)
            return {1 / v.d};
        return {~static_cast<U64>(v.d)};
    }

    throw journal::exception()[ journal::except() <<"cannot execute bitwise invert on " << lexer_component::type_name(T) ];
    return {};
}

// assign operators:
alu& alu::operator+=(const alu& rhs)
{
    lrtext(rhs)
    {
        text = text + rhs.text;
        return *this;
    }

    lr_number(rhs)
    {
        v.d += rhs.v.d;
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign add between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T)];
    return *this;
}

alu& alu::operator-=(const alu& rhs)
{
    lrtext(rhs) return *this;
    //return remove_substr(rhs.text);

    lr_number(rhs)
    {
        v.d  -= rhs.v.d;
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign substraction between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "." ];
    return *this;
}

alu& alu::operator*=(const alu& rhs)
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign multiply on strings [" << (*this)() << " *= " << rhs() << "]." ];
        return *this;
    }

    lr_number(rhs)
    {
        journal::debug()
            << color::orange5 << "alu"
            << color::white << "::"
            << color::white << rem::fn::endl << ":" << rem::fn::endl << "{" << rem::fn::endl
            << color::yellow << v.d << color::white << '(' << color::lightseagreen << lexer_component::type_name(T) << color::white << ')'
            << color::cornflowerblue << " *= "
            << color::yellow << rhs.v.d << color::white << '(' << color::lightseagreen << lexer_component::type_name(rhs.T) << color::white << ')' ;

        v.d *= rhs.v.d;
        journal::write() << color::white << " = " << color::yellow << v.d  << color::white <<  rem::fn::endl << '}' <<  rem::fn::endl ;
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign multiply between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."] ;
    return *this;
}

alu& alu::operator/=(const alu& rhs)
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign divide on strings [" << (*this)() << " /= " << rhs() << "]."] ;
        return *this;
    }

    lr_number(rhs)
    {

        if (v.d==0.0f)
        {
            throw journal::exception()[ journal::except() <<"alu: cannot divide by zero."]; // Oops plutôt erreur fatale!!
            v.d = 0.0;
            T = lex::type::Null;
            return *this;
        }
        v.d /= rhs.v.d;
        return *this;
    }
    throw journal::exception()[ journal::except() <<"cannot execute assign divide between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}

alu::~alu(){}

alu& alu::operator%=(const alu& rhs)
{
    lrtext(rhs) return *this;
    //return completely_remove_substr(rhs.text);

    lr_number(rhs)
    {
        u64 u = v.d;
        v.d = u %= static_cast<U64>(rhs.v.d);
        T &= ~lex::type::Float;
    }
    throw journal::exception()[ journal::except() << "cannot execute modulo operator on  [" << (*this)() << " %= " << rhs() << "]."];
    return *this;
}

alu& alu::operator|=(const alu& rhs)
{

    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign bitwise or on strings [" << (*this)() << " |= " << rhs() << "]."];
        return *this;
    }

    lr_number(rhs)
    {
        v.d = static_cast<U64>(v.d) | static_cast<U64>(rhs.v.d);
        return *this;
    }
    throw journal::exception()[ journal::except() <<"cannot execute assign bitwise or between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}

alu& alu::operator&=(const alu& rhs)
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign bitwise and on strings [" << (*this)() << " &= " << rhs() << "]."];
        return *this;
    }
    //    a = std::string(text + rhs.text);
    //else
    lr_number(rhs)
    {
        v.d  = static_cast<U64>(v.d) &  static_cast<U64>(rhs.v.d);
        T &= ~lex::type::Float;
        return *this;
    }
    throw journal::exception()[ journal::except() <<"cannot execute assign bitwise and between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}

alu& alu::operator^=(const alu& rhs)
{
    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign xor on strings [" << (*this)() << " ><= " << rhs() << "]."];
        return *this;
    }

    lr_number(rhs)
    {
        /// @note xor ?
        v.d = static_cast<U64>(v.d) ^ static_cast<U64>(rhs.v.d);
        T &= ~lex::type::Float;
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign xor between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}

// boolean operators:
alu alu::operator>(const alu& rhs)
{
    lrtext(rhs)
        return {text > rhs.text};

    lr_number(rhs)
        return {v.d > rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};
}

alu alu::operator<(const alu& rhs)
{
    lrtext(rhs)
        return {text < rhs.text};

    lr_number(rhs)
        return {v.d < rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};

}

alu alu::operator>=(const alu& rhs)
{
    lrtext(rhs)
        return {text >= rhs.text};

    lr_number(rhs)
        return {v.d >= rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};

}

alu alu::operator<=(const alu& rhs)
{
    lrtext(rhs)
        return {text <= rhs.text};

    lr_number(rhs)
        return {v.d <= rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};

}

alu alu::operator!=(const alu& rhs)
{
    lrtext(rhs)
        return {text != rhs.text};

    lr_number(rhs)
        return {v.d != rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};
}

alu alu::operator||(const alu& rhs)
{
    lrtext(rhs)
        return {!text.empty() || (!rhs.text.empty())};

    lr_number(rhs)
        return {v.d || rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T)];
    return {false};
}

alu alu::operator&&(const alu& rhs)
{
    lrtext(rhs)
        return {!text.empty() && (!rhs.text.empty())};

    lr_number(rhs)
        return {v.d && rhs.v.d};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations between " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return {false};
}

bool alu::operator!()
{
    return v.d ==0.0f;
}

alu alu::operator-()
{
    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot execute sign operator on string -(\"" << (*this)() << "\")."];
    }
    throw journal::exception()[ journal::except() <<"cannot execute relational operations on " << lexer_component::type_name(T)];
    return -v.d;
}

alu alu::operator+()
{
    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot execute sign operator on string +(\"" << (*this)() << "\")."];
    }

    is_number
        if (v.d < 0.0f)
            return {v.d * -1};

    throw journal::exception()[ journal::except() <<"cannot execute relational operations on " << lexer_component::type_name(T)];
    return {false};
}

alu alu::operator++(int)
{

    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot increment string (\"" << (*this)() << "\")++."];
    }

    is_number
    {
        auto f = v.d;
        alu    ff(f);
        ++f;
        v.d = f;
        return ff;
    }
    throw journal::exception()[ journal::except() <<"cannot execute increment operations on " << lexer_component::type_name(T)];
    return {false};
}

alu alu::operator++()
{
    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot increment string ++(\"" << (*this)() << "\")."];
    }

    is_number
    {
        auto f = v.d;
        ++f;
        v.d = f;
        return *this;
    }
    throw journal::exception()[ journal::except() <<"cannot execute increment operations on " << lexer_component::type_name(T)];
    return {false};
}

alu alu::operator--()
{

    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot decrement string --(\"" << (*this)() << "\")."];
    }

    is_number
    {
        auto f = v.d;
        ++f;
        v.d = f;
        return *this;
    }
    throw journal::exception()[ journal::except() <<"cannot execute decrement operations on " << lexer_component::type_name(T)];
    return {false};
}

alu alu::operator--(int)
{
    istext(*this)
    {
        throw journal::exception()[ journal::except() <<"cannot decrement string (\"" << (*this)() << "\")++."]; // oops... What if long text string?
    }

    is_number
    {
        auto f = v.d;
        alu    ff(f);
        ++f;
        v.d = f;
        return ff;
    }
    throw journal::exception()[ journal::except() <<"cannot execute decrement operations on " << lexer_component::type_name(T)];
    return {false};
}

alu alu::radical(const alu& rhs) const
{
    alu al;
    lr_number(rhs)
    {
        al = alu(std::pow(v.d, 1 / rhs.v.d));
        return al;
    }

    throw journal::exception()[ journal::except() <<"cannot execute radical operator on " << lexer_component::type_name(T)];
    return {false};
}

//    alu alu::factorial(const alu& Lhs_) const
//    {
//        journal::debug() << color::Yellow << (*this)() << color::Reset << ":" ;
//        lr_number(Lhs_)
//        {
//            int fac = 1;
//            int N = Lhs_.number<int>();
//            if (N >= 10)
//                return {};
//            for (int j = 1; j <= N; j++)
//                fac *= j;
//            journal::debug() << color::Yellow << (*this)() << color::Reset << ":" ;
//            return {fac};
//        }
//        throw journal::exception()[ journal::except() <<"cannot execute factorial operator on " << lexer_component::type_name(T) ;
//        return {false};
//    }

alu alu::factorial() const
{
    journal::debug() << rem::fn::func << color::yellow << (*this)() <<color::white << ":"  ;
    lr_number(*this)
    {
        if(v.d < 0)
        {
            throw journal::exception()[ journal::except() <<" Invalid Base number :" << color::yellow << (*this)() << color::reset] ;
            return {};
        }
        int fac = 1;
        int N = number<int>();
        if (N >= 10)
        {
            throw journal::exception()[ journal::except() <<" Base number too high." << color::yellow << (*this)() << color::reset];
            return {};
        }
        for (int j = 1; j <= N; j++)
            fac *= j;
        journal::debug() << rem::fn::func << color::yellow << fac <<color::white << ":"  ;
        return { fac };
    }
    throw journal::exception()[ journal::except() <<"cannot execute factorial operator on " << lexer_component::type_name(T)];
    return { false };

}

alu& alu::operator<<=(const alu& rhs)
{

    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign extraction/bitwise left-shift / output on strings."];
        return *this;
    }

    lr_number(rhs)
    {
        v.d  = static_cast<integers::u64>(v.d) << static_cast<integers::u64>(rhs.v.d);
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign bitwise left-shift or insert with " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}

alu& alu::operator>>=(const alu& rhs)
{

    lrtext(rhs)
    {
        throw journal::exception()[ journal::except() <<"cannot execute assign extraction/bitwise right-shift / output on strings." ];
        return *this;
    }

    lr_number(rhs)
    {
        v.d = static_cast<integers::u64>(v.d) >> static_cast<integers::u64>(rhs.v.d);;
        return *this;
    }

    throw journal::exception()[ journal::except() <<"cannot execute assign bitwise left-shift or insert with " << lexer_component::type_name(T) << " and " << lexer_component::type_name(rhs.T) << "."];
    return *this;
}




[[maybe_unused]] std::string alu::to_str() const
{
    lus::string str;
    if (T & lex::type::Bool)
    {
        str << (v.d ? "true" : "false");
        return str();
    }

    if (T & lex::type::Number)
    {
        str << v.d;
        return str();
    }

    if (T & lex::type::Text)
        return text;
    if (T & lex::type::VoidPtr)
    {
        str = "@\\{p}";
        str << v.p;
        return str();
    }

    if (T & lex::type::Null)
        str << "null";
    return str();
}

alu::operator std::string() const
{
    return to_str();
}


}
