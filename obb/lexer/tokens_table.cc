//
// Created by oldlonecoder on 24-01-27.
//



#include <lus/lexer/tokens_table.h>
#include <lus/journal.h>
namespace lus
{

    using ui::color;
/*!
 *  Default general mnemonic colors.
 *  Assign this table with specific values from the derived table.
 */
token_table::mnemonic_colours _static_mnemonic_colours_table_
{
    {lex::mnemonic::Null,                     color::white},
    {lex::mnemonic::LeftShift,               color::skyblue1},
    {lex::mnemonic::Radical,                  color::deepskyblue7},
    {lex::mnemonic::Exponent,                 color::deepskyblue7},
    {lex::mnemonic::RightShift,              color::skyblue1},
    {lex::mnemonic::Decr,                     color::dodgerblue1},
    {lex::mnemonic::Incr,                     color::dodgerblue1},
    {lex::mnemonic::AssignAdd,               color::salmon1},
    {lex::mnemonic::AssignSub,               color::salmon1},
    {lex::mnemonic::AssignMul,               color::salmon1},
    {lex::mnemonic::AssignDiv,               color::salmon1},
    {lex::mnemonic::AssignMod,               color::salmon1},
    {lex::mnemonic::AssignAnd,               color::salmon1},
    {lex::mnemonic::AssignOr,                color::salmon1},
    {lex::mnemonic::AssignXor,               color::salmon1},
    {lex::mnemonic::AssignC1,                color::salmon1},
    {lex::mnemonic::AssignLeftShift,        color::salmon1},
    {lex::mnemonic::AssignRightShift,       color::salmon1},
    {lex::mnemonic::Deref,                    color::white},
    {lex::mnemonic::LessEq,                  color::lighcoreateblue},
    {lex::mnemonic::GreaterEq,               color::lighcoreateblue},
    {lex::mnemonic::Equal,                    color::lighcoreateblue},
    {lex::mnemonic::NotEqual,                color::lighcoreateblue},
    {lex::mnemonic::Add,                      color::darkorange3},
    {lex::mnemonic::Sub,                      color::darkorange3},
    {lex::mnemonic::Mul,                      color::deepskyblue7},
    {lex::mnemonic::Indirection,              color::white},
    {lex::mnemonic::CommentCpp,              color::white},
    {lex::mnemonic::Modulo,                   color::lighcoreateblue},
    {lex::mnemonic::LessThan,                color::lighcoreateblue},
    {lex::mnemonic::GreaterThan,             color::lighcoreateblue},
    {lex::mnemonic::Assign,                   color::salmon1},
    {lex::mnemonic::BinaryAnd,               color::skyblue1},
    {lex::mnemonic::BinaryOr,                color::skyblue1},
    {lex::mnemonic::BinaryXor,               color::skyblue1},
    {lex::mnemonic::C1,                       color::skyblue1},
    {lex::mnemonic::C2,                       color::skyblue1},
    {lex::mnemonic::BinaryNot,               color::skyblue1},
    {lex::mnemonic::LogicalAnd,              color::lighcoreateblue},
    {lex::mnemonic::LogicalOr,               color::lighcoreateblue},
    {lex::mnemonic::OpenAbsOp,              color::lightsteelblue},
    {lex::mnemonic::CloseAbsOp,             color::lightsteelblue},
    {lex::mnemonic::OpenPar,                 color::gold4},
    {lex::mnemonic::ClosePar,                color::gold4},
    {lex::mnemonic::OpenIndex,                  color::darkolivegreen2},
    {lex::mnemonic::CloseIndex,                 color::darkolivegreen2},
    {lex::mnemonic::OpenBrace,                  color::grey69},
    {lex::mnemonic::CloseBrace,                 color::grey69},
    {lex::mnemonic::BeginComment,            color::orange3},
    {lex::mnemonic::EndComment,              color::orange3},
    {lex::mnemonic::Div,                      color::deepskyblue7},
    {lex::mnemonic::Comma,                    color::violet},
    {lex::mnemonic::Scope,                    color::violet},
    {lex::mnemonic::Semicolon,                color::violet},
    {lex::mnemonic::Colon,                    color::violet},
    {lex::mnemonic::Range,                    color::violet},
    {lex::mnemonic::Factorial,                color::deepskyblue4},
    {lex::mnemonic::Positive,                 color::white},
    {lex::mnemonic::Negative,                 color::white},
   {lex::mnemonic::SQuote,                   color::white},
   {lex::mnemonic::DQuote,                   color::white},
    {lex::mnemonic::Ternary,                  color::white},
    {lex::mnemonic::Hash,                     color::white},
    {lex::mnemonic::Eos,                      color::white},
    {lex::mnemonic::Dot,                      color::violet},
    {lex::mnemonic::Return,                   color::dodgerblue2},
    {lex::mnemonic::If,                       color::dodgerblue2},
    {lex::mnemonic::Pi,                       color::gold1},
    {lex::mnemonic::Number,                   color::aquamarine2},
    {lex::mnemonic::U8,                       color::aquamarine2},
    {lex::mnemonic::U16,                      color::aquamarine2},
    {lex::mnemonic::U32,                      color::aquamarine2},
    {lex::mnemonic::U64,                      color::aquamarine2},
    {lex::mnemonic::I8,                       color::aquamarine2},
    {lex::mnemonic::I16,                      color::aquamarine2},
    {lex::mnemonic::I32,                      color::aquamarine2},
    {lex::mnemonic::I64,                      color::aquamarine2},
    {lex::mnemonic::Float,                    color::aquamarine2},
    {lex::mnemonic::String,                   color::aquamarine2},
    {lex::mnemonic::Then,                     color::dodgerblue2},
    {lex::mnemonic::Else,                     color::dodgerblue2},
    {lex::mnemonic::Const,                    color::white},
    {lex::mnemonic::Include,                  color::white},
    //{lex::mnemonic::Module,                   color::white},
    {lex::mnemonic::At,                       color::white},
    {lex::mnemonic::Prime,                    color::white},
    {lex::mnemonic::Do,                       color::dodgerblue2},
    {lex::mnemonic::While,                    color::dodgerblue2},
    {lex::mnemonic::For,                      color::dodgerblue2},
    {lex::mnemonic::Until,                    color::dodgerblue2},
    {lex::mnemonic::Repeat,                   color::dodgerblue2},
    {lex::mnemonic::Switch,                   color::dodgerblue2},
    {lex::mnemonic::Case,                     color::dodgerblue2},
    {lex::mnemonic::Type,                     color::white},
    {lex::mnemonic::LowHex,                  color::white},
    {lex::mnemonic::UpHex,                   color::white},
    {lex::mnemonic::Cosinus,                  color::springgreen4},
    {lex::mnemonic::ArcCosinus,              color::springgreen4},
    {lex::mnemonic::Tangent,                  color::springgreen4},
    {lex::mnemonic::ArcTangent,              color::springgreen4},
    {lex::mnemonic::Sinus,                    color::springgreen4},
    {lex::mnemonic::ArcSinus,                color::springgreen4},
    {lex::mnemonic::Object,                   color::springgreen4},
    {lex::mnemonic::Static,                   color::grey70},
    {lex::mnemonic::This,                     color::springgreen4},
    {lex::mnemonic::UnShadow,                 color::white},
    {lex::mnemonic::Catch,                    color::yellow5},
    {lex::mnemonic::Throw,                    color::yellow5},
    {lex::mnemonic::Noop,                      color::yellow5}

};

/*!
 *  Default general lexemes type colors.
 *  Assign this table with specific values from the derived table.
 */
token_table::type_colours _static_type_colours_table_
{
    {lex::type::Assign,    color::cadetblue},
    {lex::type::Number,    color::cyan2},
    {lex::type::Keyword,   color::cornflowerblue},
    {lex::type::Operator,  color::lightcoral},
    {lex::type::Binary,    color::cornsilk1},
    {lex::type::Text,      color::darkslategray3},
    {lex::type::Id,        color::white},
    {lex::type::Punc,      color::yellow},
    {lex::type::Prefix,    color::cadetblue},
    //...
};



/*!
 * @brief This is the default complete tokens reference of the Scrat Language.
 * @return
 */
[[maybe_unused]] size_t token_table::set_reference_table()
{
    if(!ref_table.empty())
    {
        journal::warning() << rem::cc::notempty << journal::eol;
    }
    ref_table = lex_token::list{
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::LeftShift,
            .name   = {"LeftShift"},
            .d      = lex::operand::Shift,
            .token_location    = { .begin = lex::lexem::LeftShift },
            .flags  = { .V = 1 }
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Number|lex::type::Const,
            .m     = lex::mnemonic::Null,
            .name  = "Null",
            .d     = lex::operand::Identifier,
            .token_location   = { .begin = lex::lexem::Null },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::UnShadow,
            .name  = "Unshadow",
            .d     = lex::operand::Scope,
            .token_location   = { .begin = lex::lexem::Unshadow },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::OpenPair,
            .sem = lex::type::Binary|lex::type::Operator|lex::type::OpenPair|lex::type::Punc,
            .m     = lex::mnemonic::OpenAbsOp, // |< x+1 >|;
            //                               ~~
            //                               ^
            .name  = "OpenAbsOp",
            .d     = lex::operand::Parenthese,
            .token_location   = {.begin = lex::lexem::AbsBegin },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::ClosePair,
            .sem = lex::type::Binary|lex::type::Operator|lex::type::OpenPair|lex::type::Punc,
            .m     = lex::mnemonic::CloseAbsOp, // |< x+1 >|;
            //                                       ~~
            //                                       ^
            .name  = "CloseAbsOp",
            .d     = lex::operand::Parenthese,
            .token_location   = {.begin = lex::lexem::AbsEnd },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::Radical,
            .name  = "Radical",
            .d     = lex::operand::Exponent,
            .token_location   = {.begin = lex::lexem::Radical },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::Exponent,
            .name    = "Exponent",
            .d     = lex::operand::Exponent,
            .token_location   = {.begin = lex::lexem::Exponent },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::RightShift,
            .name  = "RightShift",
            .d     = lex::operand::Shift,
            .token_location   = {.begin = lex::lexem::RightShift },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::BinaryXor,
            .name  = "BinaryXor",
            .d     = lex::operand::Bits,
            .token_location   = {.begin = lex::lexem::Xor },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Prefix|lex::type::Operator|lex::type::Unary,
            .m     = lex::mnemonic::Deref,
            .name  = "Deref",
            .d     = lex::operand::Deref,
            .token_location   = {.begin = lex::lexem::Deref },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Deref,
            .name  = "DerefUtf",
            .d     = lex::operand::Bits,
            .token_location   = {.begin = "➪" },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Unary,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Decr,
            .name  = "Decr",
            .d     = lex::operand::Unary,
            .token_location   = {.begin = lex::lexem::Decr },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Unary,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Incr,
            .name  = "Incr",
            .d     = lex::operand::Unary,
            .token_location   = {.begin = lex::lexem::Incr },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Assign,
            .sem   = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m     = lex::mnemonic::AssignAdd,
            .name  = "AssignAdd",
            .d     = lex::operand::Assign,
            .token_location   = {.begin = lex::lexem::AssignAdd},
            .flags = {.V=1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignMul,
            .name  = "AssignMul",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignMul},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignDiv,
            .name  = "AssignDiv",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignDiv},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignMod,
            .name  = "AssignMod",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignMod},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignOr,
            .name  = "AssignOr",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignXor,
            .name  = "AssignXor",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignXor},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignC1,
            .name  = "AssignC1",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignC1},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignLeftShift,
            .name  = "AssignLeftShift",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignLShift},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignRightShift,
            .name  = "AssignRightShift",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignRShift},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::GreaterEq,
            .name  = "GreaterEq",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::GreaterEqual},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::Equal,
            .name  = "Equal",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::Equal},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::NotEqual,
            .name  = "NotEqual",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::NotEqual},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::NotEqual,
            .name  = "NotEqualAlt",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = "<>"},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Add,
            .name  = "Addition",
            .d      = lex::operand::Addition,
            .token_location    = {.begin = lex::lexem::Addition},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Sub,
            .name  = "Subtract",
            .d      = lex::operand::Addition,
            .token_location    = {.begin = lex::lexem::Sub},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Mul,
            .name  = "Multiply",
            .d      = lex::operand::Product,
            .token_location    = {.begin = lex::lexem::Multiply},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::LineComment,
            .sem    = lex::type::LineComment|lex::type::Operator,
            .m      = lex::mnemonic::CommentCpp,
            .name  = "CommentCpp",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentCpp},
            .flags  = {.V = 0}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Modulo,
            .name  = "Modulo",
            .d      = lex::operand::Product,
            .token_location    = {.begin = lex::lexem::Modulo},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LessThan,
            .name  = "LessThan",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::LessThan},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::GreaterThan,
            .name  = "GreaterThan",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::GreaterThan},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::Assign,
            .name  = "Assign",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::Assign},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::BinaryAnd,
            .name  = "BinaryAnd",
            .d      = lex::operand::Bits,
            .token_location    = {.begin = lex::lexem::BinaryAnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::BinaryOr,
            .name  = "BinaryOr",
            .d      = lex::operand::Bits,
            .token_location    = {.begin = lex::lexem::BinaryOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Prefix,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::C2, // Tow's complement
            .name  = "TwoComplement",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::C2},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Prefix,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::C1, // Tow's complement
            .name  = "OneComplement",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::C1},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Unary,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::BinaryNot, // Tow's complement
            .name  = "BinaryNot",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::Not},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LogicalAnd, // Tow's complement
            .name  = "LogicalAnd",
            .d      = lex::operand::Bool_and,
            .token_location    = {.begin = lex::lexem::BoolAnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LogicalOr, // Tow's complement
            .name  = "LogicalOr",
            .d      = lex::operand::Bool_or,
            .token_location    = {.begin = lex::lexem::BoolOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenPar, // Tow's complement
            .name  = "OpenPar",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::OpenPar},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::ClosePar, // Tow's complement
            .name  = "ClosePar",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::ClosePar},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenIndex, // Tow's complement
            .name  = "OpenIndex",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::OpenIndex},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::CloseIndex, // Tow's complement
            .name  = "CloseIndex",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::CloseIndex},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenBrace, // Tow's complement
            .name  = "OpenBrace",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::BraceBegin},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::CloseBrace, // Tow's complement
            .name  = "CloseBrace",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::BraceEnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::BlocComment,
            .sem    = lex::type::BlocComment|lex::type::Operator,
            .m      = lex::mnemonic::BeginComment, // Tow's complement
            .name  = "BeginBlocComment",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentBegin},
            .flags  = {.V = 0}
        },
        {
            .prim   = lex::type::BlocComment,
            .sem    = lex::type::BlocComment|lex::type::Operator,
            .m      = lex::mnemonic::EndComment, // Tow's complement
            .name  = "EndBlocComment",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentEnd},
            .flags  = {.V = 0}
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Operator|lex::type::Binary,
            .m = lex::mnemonic::Div,
            .name  = "Division",
            .d = lex::operand::Product,
            .token_location = {.begin = lex::lexem::Division},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Comma,
            .name  = "Comma",
            .d = lex::operand::Comma,
            .token_location = {.begin = lex::lexem::Comma},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Scope,
            .name  = "Scope",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Scope},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Punc,
            .m = lex::mnemonic::Semicolon,
            .name  = "SemiColon",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Semicolon},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Colon,
            .name  = "Colon",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Colon},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Range,
            .name  = "Range",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Range},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Postfix,
            .sem = lex::type::Unary|lex::type::Postfix|lex::type::Operator,
            .m = lex::mnemonic::Factorial,
            .name  = "Factorial",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Factorial},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Sign|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Positive,
            .name  = "Positive",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Positive},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Sign|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Negative,
            .name  = "Negative",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Negative},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Text,
            .sem = lex::type::Text|lex::type::Leaf|lex::type::Operator,
            .m = lex::mnemonic::SQuote,
            .name  = "SingleQuote",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Squote},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Text,
            .sem = lex::type::Text|lex::type::Leaf|lex::type::Operator,
            .m = lex::mnemonic::DQuote,
            .name  = "DoubleQuote",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Dquote},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Operator|lex::type::Binary,
            .m = lex::mnemonic::Ternary,
            .name  = "Ternary",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Ternary},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Hash,
            .name  = "Hash",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Hash},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Eos,
            .name  = "EosMark",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Eos},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Punc|lex::type::Operator,
            .m = lex::mnemonic::Dot,
            .name  = "Dot",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Dot},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Return,
            .name  = "Return",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Return},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::If,
            .name  = "If",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::If},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Number,
            .sem = lex::type::Number|lex::type::Leaf|lex::type::Float|lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Pi,
            .name  = "Pi",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Pi},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Number,
            .sem = lex::type::Number|lex::type::Leaf|lex::type::Float|lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Pi,
            .name  = "PiUtf",
            .d = lex::operand::Identifier,
            .token_location = {.begin = "π"},
            .flags{.V=1,.U=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Number|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Number,
            .name  = "Number",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Number},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U8|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U8,
            .name  = "U8",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U8},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U16|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U16,
            .name  = "U16",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U16},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U32|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U32,
            .name  = "U32",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U32},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U64|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U64,
            .name  = "U64",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U64},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I8|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::I8,
            .name  = "I8",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I8},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I16|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator                ,
            .m = lex::mnemonic::I16,
            .name  = "I16",
            .d = lex::operand::Identifier, .token_location = {.begin = lex::lexem::I16},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I32|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator                ,
            .m = lex::mnemonic::I32,
            .name  = "I32",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I32},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I64|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::I64,
            .name  = "I64",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I64},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Float|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator ,
            .m = lex::mnemonic::Float,
            .name  = "Float",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Float},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Text|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::String,
            .name  = "String",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::String},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Then,
            .name  = "Then",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Then},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Else,
            .name  = "Else",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Else},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Const,
            .name  = "Const",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Const},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Include,
            .name  = "Include",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Include},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Amu,
            .name  = "Amu",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Amu},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::At,
            .name  = "At",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::At},.flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Prime,
            .name  = "Prime",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Prime},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Do,
            .name  = "Do",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Do},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::While,
            .name  = "While",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::While},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::For,
            .name  = "For",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::For},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Until,
            .name  = "Until",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Until},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Repeat,
            .name  = "Repeat",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Repeat},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Switch,
            .name  = "Switch",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Switch},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Case,
            .name  = "Case",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Case},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Type,
            .name  = "Type",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Type},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Leaf|lex::type::Keyword|lex::type::Operator|lex::type::Hex,
            .m = lex::mnemonic::LowHex,
            .name  = "LowHex",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::LowHex},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Leaf|lex::type::Keyword|lex::type::Operator|lex::type::Hex,
            .m = lex::mnemonic::UpHex,
            .name  = "UpHex",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::UpHex},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Cosinus,
            .name  = "Cosinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Cosinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcCosinus,
            .name  = "ArcCosinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcCosinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Tangent,
            .name  = "Tangent",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Tangent},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcTangent,
            .name  = "ArcTangent",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcTangent},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Sinus,
            .name  = "Sinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Sinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcSinus,
            .name  = "ArcSinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcSinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Object,
            .name  = "Object",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Object},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Static,
            .name  = "Static",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Static},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::This,
            .name  = "This",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::This},
            .flags{.V=1}
        }
    };

    return ref_table.size();
}




// size_t ArithmeticLexemes::DeclareTable()
// {
//     return token_table::DeclareTable();
// }


token_table::~token_table()
{
    ref_table.clear(); //oops!!!!!!

}

lex_token token_table::scan(const char* C)
{
    journal::debug() << " scanning[" << color::yellow << *C <<  color::reset << ']' << journal::endl;
    if(ref_table.empty())
    {
        journal::warning() << " tokens reference table is empty";
        return {};
    }

    int unicode = 0;
    if (!*C)
    {
        journal::info() << rem::cc::eof << journal::endl;
        return {};
    }

    for (auto token : ref_table)
    {
        //journal::Debug() << "Token Ref loop:'" << Color::Yellow << token.name << Color::Reset << ": (" << Color::HotPink4 << token.token_location.begin << Color::Reset << "<=>" << Color::Lime << *C << Color::Reset << "):";
        std::string_view::iterator crs = C;
        std::string_view::iterator rtxt = token.token_location.begin;
        unicode = 0; // oops...
        //std::size_t sz = std::strlen(rtxt);

        if(*crs != *rtxt) {
            //journal::Debug() << *crs << " != " << *rtxt;
            continue;
        }
        //journal::Debug() << *crs << " <==> " << *rtxt;
        while ((rtxt && crs) && (*crs && *rtxt) && (*crs == *rtxt))
        {
            if (*crs < 0)
                ++unicode; ///< @note oui/ yes; Soon/Bientôt je supporte quelques symboles UTF-8 (pi, xor,...)

            ++crs;
            ++rtxt;
            //journal::Debug() << *crs << " <==> " << ( rtxt ?  *rtxt : ' ');
        }
        if (!rtxt || (*rtxt == 0))
        {
            if (*crs && !isspace(*crs))
            {
                if ((isalnum(*crs) || (*crs == '_')) && !token.has_type(lex::type::Operator|lex::type::Punc|lex::type::Keyword))
                    continue;
            }

            token.token_location.begin = C;
            token.token_location.end = --crs;
            token.token_location.length = (token.token_location.end - token.token_location.begin)+1;
            journal::info() << "matched : " << token.type_name() << journal::endl;
            return token;
        }
    }

    journal::debug() << " No match." << journal::endl;
    return {};
}


lex_token token_table::scan(lex::mnemonic::T _m) const
{
    for (auto t : ref_table) if (t.m == _m) return t;
    return {};
}


lex_token token_table::operator[](lex::mnemonic::T _m) const
{
    for (auto t : ref_table) if (t.m == _m) return t;
    return {};
}


token_table &token_table::operator<<(lex_token &NewToken)
{
    prod_table.emplace_back(NewToken);
    return *this;
}

void token_table::dump_reference_table() const
{
    journal::debug() << " Dump the Tokens Reference Table:\n";

    for(auto const& token : ref_table)
        journal::write() << token.details();
}



lex_token const &token_table::get(std::string_view mnemonic_name)
{
    if(ref_table.empty())
        throw journal::exception() [ journal::error() << " Tokens Reference Table is empty!"];

    for(auto const& Token : ref_table)
        if(Token.name == mnemonic_name) return Token;

    throw journal::exception() [ journal::error() << " Tokens identified by '" << color::yellow << mnemonic_name << color::reset << "' Is not in this table."];
}

void token_table::dump_production_table()
{
    journal::debug() << " Dump the Tokens Product Table:" << journal::eol;

    for(auto const& token : prod_table)
        journal::write() << token.details();
}

lex_token const &token_table::get(lex::mnemonic::T M)
{
    for(auto const& token : ref_table)
    {
        if(token.m == M) return token;
    }
    throw journal::exception()[ journal::error()  << " Tokens identified by Enumerator " << color::yellow << static_cast<int>(M) << color::reset << " Is not in this table."];
}


}
