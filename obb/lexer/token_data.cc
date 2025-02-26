//
// Created by oldlonecoder on 24-01-27.
//

#include <lus/lexer/tokens_table.h>
#include <lus/lexer/sscan.h>
#include <lus/geometry.h>
#include <lus/journal.h>

#include <format>

static std::string_view NullMsg { "No String" };


namespace lus
{




std::map<lus::sscan::numeric::details::size_type, lex::type::T> nummap =
{
    {lus::sscan::numeric::details::size_type::I8  , lex::type::I8  },
    {lus::sscan::numeric::details::size_type::I16 , lex::type::I16 },
    {lus::sscan::numeric::details::size_type::I32 , lex::type::I32 },
    {lus::sscan::numeric::details::size_type::I64 , lex::type::I64 },
    {lus::sscan::numeric::details::size_type::U8  , lex::type::U8  },
    {lus::sscan::numeric::details::size_type::U16 , lex::type::U16 },
    {lus::sscan::numeric::details::size_type::U32 , lex::type::U32 },
    {lus::sscan::numeric::details::size_type::U64 , lex::type::U64 },
    {lus::sscan::numeric::details::size_type::F32 , lex::type::F32 },
    {lus::sscan::numeric::details::size_type::F64 , lex::type::F64 },
    {lus::sscan::numeric::details::size_type::F128, lex::type::F128}
};


/*!
 * @brief get the text of this token.
 * @return string_view content.
 *
 * @note [JetBrains CLion: warning from clang inspection: "The address of the local variable 'sv' may escape the function" ]
 *       - 1 : I build that string_view from instance's private member data that lives the life of the token.
 *       - 2 : std::string_view is supposed to be exactly a representation of the non-copied char array, not a (new) copy of that array.
 *       - 3 : std::string_view IS MEANT to quit ( copy itself ) the scope for presenting and (rdonly) accessing the inner char array it represents!
 *       - 4 : I return "a new (stack) copy" of std::string_view!
 *       - 5 : That is a huge and annoying nonsense...
 *       - 6 : For now, that inspection is disabled.
 *
 */
std::string_view lex_token::location_data::operator()()
{
    if(!begin) return NullMsg;
    //journal::debug() << " length: " << length << journal::eol;
    if(!end)
    {
        // In case of that token is a reference token, taken from the reference table, the end pointer is set to nullptr.
        std::string_view sv(begin);
        length = sv.length();
        return sv;
    }
    return {begin,length ? length : length+1};
}




[[maybe_unused]] std::string lex_token::location_data::position() const
{
    lus::string Txt = "%d,%d";
    return { (Txt << line << column)() };
}

lex_token::location_data &lex_token::location_data::operator=(const lus::sscan::location_data &Data)
{
    line   = Data.line;
    column = Data.col;
    offset = Data.offset;
    return *this;
}


//lex_token::~lex_token(){}

std::string lex_token::semantic_names() const
{
    return lus::lexer_component::type_name(sem);
}


std::string lex_token::type_name() const
{
    return lus::lexer_component::type_name(prim);
}


std::string lex_token::details(bool Frame) const
{
    lus::string Out;
    auto T = text();
    Out << std::format("{:>4d},{:<4d}", token_location.column, token_location.line) <<
        color::reset << "[" <<
        color::yellow << std::format("{:<20s}",name) <<
        color::reset << "] Primary Type:" <<
        color::deepskyblue7 << std::format("{:<12s}", lexer_component::type_name(prim)) <<
        color::reset << "{" <<
        color::turquoise4 << std::format("{:<32s}",lexer_component::type_name(sem)) <<
        color::reset << "}" << "text: " << color::yellow <<  std::string(T.begin(), T.end()) << color::reset;

    return Out();
}


std::string lex_token::mark(const char* src, bool a_colorize) const
{
    // 1 - Locate Beginning of the line:

    if (!token_location.end || !src) return "no source text";

    // Scan backward:
    auto line_begin = token_location.begin;
    while ((line_begin > src) && (*line_begin != '\r') && (*line_begin != '\n')) --line_begin;
    // Scan forward:

    auto line_end = token_location.begin;

    while (*line_end && (*line_end != '\r') && (*line_end != '\n') ) ++line_end;

    lus::string Out = std::string(line_begin, line_end);
    // @todo : Colorize all tokens on the same line here.
    Out << '\n' << std::string(token_location.column-1,' ') << lus::glyph::arrow_up;

    return Out();
}




void lex_token::numeric_tr()
{
    if(num_data.seq.empty())
        throw journal::exception()[ journal::error() << " Cannot call lex_token::numeric_tr on un-scanned or non-numeric token." ];
    sem = lex::type::Number | lex::type::Const | nummap[num_data.size] | lex::type::Leaf;
}


} // lex
