//
// Created by oldlonecoder on 8/22/24.
//

//#ifndef LEXER_TYPES_H
//#define LEXER_TYPES_H
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



#pragma once

#include <map>
#include <lus/journal.h>
#include <lus/lexer/export.h>


namespace lus
{

using namespace integers;
namespace lex::type
{
    using T = u64;

    constexpr T Number      = 0x000000000001;
    constexpr T Text        = 0x000000000002;
    constexpr T VoidPtr     = 0x000000000004;
    constexpr T Any         = 0x000000000008;
    constexpr T Leaf        = 0x000000000010;
    constexpr T Sign        = 0x000000000020;
    constexpr T I8          = 0x000000000040;
    constexpr T I16         = 0x000000000080;                                                                              // 0x7F41
    constexpr T I32         = 0x000000000100;
    constexpr T I64         = 0x000000000200;
    constexpr T U8          = 0x000000000400;
    constexpr T U16         = 0x000000000800;
    constexpr T U32         = 0x000000001000;
    constexpr T U64         = 0x000000002000;
    constexpr T Float       = 0x000000004000;                                                                              // real: f32, f64, f128... ^^
    constexpr T Var         = 0x000000008000;                                                                              // Ne pas oublier d'ajouter ce type a toutes "variables"
    constexpr T Bloc        = 0x000000010000;
    constexpr T Pipe        = 0x000000020000;
    constexpr T Keyword     = 0x000000040000;
    constexpr T Unary       = 0x000000080000;
    constexpr T Prefix      = 0x000000100000;
    constexpr T Postfix     = 0x000000200000;
    constexpr T Operator    = 0x000000400000;
    constexpr T Binary      = 0x000000800000;
    constexpr T Function    = 0x000001000000;
    constexpr T FunctionPtr = 0x000002000000;
    constexpr T Object      = 0x000004000000;
    constexpr T Pointer     = 0x000008000000;
    constexpr T Type        = 0x000010000000;
    constexpr T Id          = 0x000020000000;
    constexpr T Ref         = 0x000040000000;
    constexpr T Punc        = 0x000080000000;
    constexpr T Assign      = 0x000100000000;
    constexpr T Bool        = 0x000200000000;
    constexpr T Hex         = 0x000400000000;
    constexpr T OpenPair    = 0x000800000000;
    constexpr T ClosePair   = 0x001000000000;
    constexpr T Const       = 0x002000000000;
    constexpr T Static      = 0x008000000000;                                                                              ///< Flag set at the parser phase when applicable.
    constexpr T F32         = 0x010000000000;
    constexpr T F64         = 0x020000000000;
    constexpr T F128        = 0x040000000000;
    constexpr T OctalFormat = 0x080000000000;
    constexpr T BinFormat   = 0x100000000000;
    constexpr T LineComment = 0x200000000000;
    constexpr T BlocComment = 0x400000000000;
    constexpr T Literal     = 0x800000000000;                                                                              ///< Literal types { number, string/Text };
    constexpr T Null        = 0x1000000000000000;
    constexpr T Integer     = type::I8 | type::I16 | type::I32 | type::I64 | type::U8 | type::U16 | type::U32 | type::U64;
    constexpr T Unsigned    = type::U8 | type::U16 | type::U32 | type::U64;
}


namespace lex::mnemonic
{
    using     T                  = uint16_t;
    constexpr T Null             = 0;
    constexpr T LeftShift        = 1;
    constexpr T Radical          = 2;
    constexpr T Exponent         = 3;
    constexpr T RightShift       = 4;
    constexpr T Decr             = 5;
    constexpr T Incr             = 6;
    constexpr T AssignAdd        = 7;
    constexpr T AssignSub        = 8;
    constexpr T AssignMul        = 9;
    constexpr T AssignDiv        = 10;
    constexpr T AssignMod        = 11;
    constexpr T AssignAnd        = 12;
    constexpr T AssignOr         = 13;
    constexpr T AssignXor        = 14;
    constexpr T AssignC1         = 15;
    constexpr T AssignLeftShift  = 16;
    constexpr T AssignRightShift = 17;
    constexpr T Deref            = 18;
    constexpr T LessEq           = 19;
    constexpr T GreaterEq        = 20;
    constexpr T Equal            = 21;
    constexpr T NotEqual         = 22;       //        !=         <>
    constexpr T Add              = 23;
    constexpr T Sub              = 24;
    constexpr T Mul              = 25;
    constexpr T Indirection      = 26;
    constexpr T CommentCpp       = 27;
    constexpr T Modulo           = 28;
    constexpr T LessThan         = 29;
    constexpr T GreaterThan      = 30;
    constexpr T Assign           = 31;
    constexpr T BinaryAnd        = 32;
    constexpr T BinaryOr         = 33;
    constexpr T BinaryXor        = 34;
    constexpr T C1               = 35;       //        complement a 1
    constexpr T C2               = 36;
    constexpr T BinaryNot        = 37;       //
    constexpr T LogicalAnd       = 38;
    constexpr T LogicalOr        = 39;
    constexpr T OpenAbsOp        = 40;
    constexpr T CloseAbsOp       = 41;
    constexpr T OpenPar          = 42;
    constexpr T ClosePar         = 43;
    constexpr T OpenIndex        = 44;
    constexpr T CloseIndex       = 45;
    constexpr T OpenBrace        = 46;
    constexpr T CloseBrace       = 47;
    constexpr T BeginComment     = 48;
    constexpr T EndComment       = 49;
    constexpr T Div              = 50;
    constexpr T Comma            = 51;
    constexpr T Scope            = 52;
    constexpr T Semicolon        = 53;
    constexpr T Colon            = 54;
    constexpr T Range            = 55;
    constexpr T Factorial        = 56;
    constexpr T Positive         = 57;
    constexpr T Negative         = 58;
    constexpr T SQuote           = 59;       //        '
    constexpr T DQuote           = 60;       //        "
    constexpr T Ternary          = 61;       //        ?          :
    constexpr T Hash             = 62;       //
    constexpr T Eos              = 63;
    constexpr T Dot              = 64;
    constexpr T Return           = 65;
    constexpr T If               = 66;
    constexpr T Pi               = 67;
    constexpr T Number           = 68;
    constexpr T U8               = 69;
    constexpr T U16              = 70;
    constexpr T U32              = 71;
    constexpr T U64              = 72;
    constexpr T I8               = 73;
    constexpr T I16              = 74;
    constexpr T I32              = 75;
    constexpr T I64              = 76;
    constexpr T Float            = 77;
    constexpr T String           = 78;
    constexpr T Then             = 79;
    constexpr T Else             = 80;
    constexpr T Const            = 89;
    constexpr T Include          = 90;
    constexpr T Amu              = 91;
    constexpr T At               = 92;
    constexpr T Prime            = 93;
    constexpr T Do               = 94;
    constexpr T While            = 95;
    constexpr T For              = 96;
    constexpr T Until            = 97;
    constexpr T Repeat           = 98;
    constexpr T Switch           = 99;
    constexpr T Case             = 100;
    constexpr T Type             = 101;
    constexpr T LowHex           = 102;
    constexpr T UpHex            = 103;
    constexpr T Cosinus          = 104;
    constexpr T ArcCosinus       = 105;
    constexpr T Tangent          = 106;
    constexpr T ArcTangent       = 107;
    constexpr T Sinus            = 108;
    constexpr T ArcSinus         = 109;
    constexpr T Object           = 110;
    constexpr T Static           = 111;
    constexpr T This             = 112;
    constexpr T UnShadow         = 114;
    constexpr T Catch            = 115;
    constexpr T Throw            = 116;
    constexpr T Try              = 117;
    constexpr T Noop             = 118;
    constexpr T LineComment      = 119;
    constexpr T BlocComment      = 120;
    constexpr T Identifier       = 1000;
    constexpr T Numeric          = 1001;

} // namespace mnemonic


namespace lex::lexem
{

using Value = const char*;//std::string_view;
constexpr Value Null          = "null";
constexpr Value LeftShift     = "<<";
constexpr Value Radical       = "^/";
constexpr Value Exponent      = "^";
constexpr Value RightShift    = ">>";
constexpr Value Decr          = "--";
constexpr Value Incr          = "++";
constexpr Value AssignAdd     = "+=";
constexpr Value AssignSub     = "-=";
constexpr Value AssignMul     = "*=";
constexpr Value AssignDiv     = "/=";
constexpr Value AssignMod     = "%=";
constexpr Value AssignAnd     = "&=";
constexpr Value AssignOr      = "|=";
constexpr Value AssignXor     = "><=";
constexpr Value AssignC1      = "`="; // Insérer AssignCompletment à 2 =>  { ``=  }
constexpr Value AssignLShift  = "<<=";
constexpr Value AssignRShift  = ">>=";
constexpr Value Deref         = "->";
constexpr Value LessEqual     = "<=";
constexpr Value GreaterEqual  = ">=";
constexpr Value Equal         = "==";
constexpr Value NotEqual      = "!=";  // != <>
constexpr Value Addition      = "+";
constexpr Value Sub           = "-";
constexpr Value Multiply      = "*";
constexpr Value Indirection   = "*";
constexpr Value CommentCpp    = "//";
constexpr Value Modulo        = "%";
constexpr Value Xor           = "><";
constexpr Value LessThan      = "<";
constexpr Value GreaterThan   = ">";
constexpr Value Assign        = "=";
constexpr Value BinaryAnd     = "&";
constexpr Value BinaryOr      = "|";
constexpr Value C1            = "`"; ///< compl&eacute;ment &agrave; 1
constexpr Value C2            = "``";///< compl&eacute;ment &agrave; 2
constexpr Value Not           = "!";
constexpr Value BoolAnd       = "&&";
constexpr Value BoolOr        = "||";
constexpr Value AbsBegin      = "|<";// |< absolute value expr >|
constexpr Value AbsEnd        = ">|";
constexpr Value OpenPar       = "(";
constexpr Value ClosePar      = ")";
constexpr Value OpenIndex     = "[";
constexpr Value CloseIndex    = "]";
constexpr Value BraceBegin    = "{";
constexpr Value BraceEnd      = "}";
constexpr Value CommentBegin  = "/*";
constexpr Value CommentEnd    = "*/";
constexpr Value Division      = "/";
constexpr Value Comma         = ",";
constexpr Value Scope         = "::";
constexpr Value Semicolon     = ";";
constexpr Value Colon         = ":";
constexpr Value Range         = "..";
constexpr Value Factorial     = "!";
constexpr Value Positive      = "+";
constexpr Value Negative      = "-";
constexpr Value Squote        = "'";  // '
constexpr Value Dquote        = "\""; // "
constexpr Value Ternary       = "?";  // ? :
constexpr Value Hash          = "#";  // #
constexpr Value Eos           = "$";
constexpr Value Dot           = ".";
constexpr Value Return        = "return";
constexpr Value If            = "if";
constexpr Value Pi            = "pi";
constexpr Value Number        = "number";
constexpr Value U8            = "u8";
constexpr Value U16           = "u16";
constexpr Value U32           = "u32";
constexpr Value U64           = "u64";
constexpr Value I8            = "i8";
constexpr Value I16           = "i16";
constexpr Value I32           = "i32";
constexpr Value I64           = "i64";
constexpr Value Float         = "real";
constexpr Value String        = "string";
constexpr Value Then          = "then";
constexpr Value Else          = "else";
constexpr Value Const         = "const";
constexpr Value Include       = "include";
constexpr Value Amu           = "amu";
constexpr Value At            = "@";
constexpr Value Prime         = "`"; ///@todo change...
constexpr Value Do            = "do";
constexpr Value While         = "while";
constexpr Value For           = "for";
constexpr Value Until         = "until";
constexpr Value Repeat        = "repeat";
constexpr Value Switch        = "switch";
constexpr Value Case          = "case";
constexpr Value Type          = "type";
constexpr Value LowHex        = "0x";
constexpr Value UpHex         = "0X";
constexpr Value Cosinus       = "cos";
constexpr Value ArcCosinus    = "acos";
constexpr Value Tangent       = "tan";// tan(4*a*m)  - sin(4ac) sina
constexpr Value ArcTangent    = "atan";
constexpr Value Sinus         = "sin";
constexpr Value ArcSinus      = "asin";
constexpr Value Object        = "object";
constexpr Value Static        = "static";
constexpr Value This          = "me";
constexpr Value Unshadow      = ".::"; // If a local variable shadows a higher scoped variable, then this operator will address the variable from within the first bloc where the given variable is scoped.
constexpr Value Catch         = "catch";
constexpr Value Throw         = "throw";
constexpr Value Try           = "try";
constexpr Value LineComment   = "//";
constexpr Value BlocComment   = "/*";

constexpr Value Identifier    = "Identifier/Symbol";
constexpr Value Numeric       = "Literal Number";

} // namespace lexem


namespace lex::operand
{
using Index = uint8_t;
constexpr Index Scope      = 0;
constexpr Index Assign_rhs = 1; //  A = B = ER!
constexpr Index Deref      = 2;
constexpr Index Prefix     = 3;
constexpr Index Postfix    = 3;
constexpr Index Unary      = 3;
constexpr Index Parenthese = 5;
constexpr Index Exponent   = 6;
constexpr Index Bits       = 7;
constexpr Index Product    = 8;
constexpr Index Addition   = 9;
constexpr Index Shift      = 10;
constexpr Index Equality   = 11;
constexpr Index Comp       = 12;
constexpr Index Bool_and   = 13;
constexpr Index Bool_xor   = 14;
constexpr Index Bool_or    = 15;
constexpr Index Boolean    = 16;
constexpr Index Ternary    = 17;
constexpr Index Comma      = 18;
constexpr Index Identifier = 19;
constexpr Index Assign     = 20; // a + b * m = 0 - 1 ( assign is right hand side association so the operator has lowest priority)
constexpr Index Noop_      = 21;

} // namespace operand

struct LUSLEXERLIB lexer_component
{

    static std::map<lex::type::T,     const char*> type_enums;
    //static std::map<lex::Mnemonic::T, std::string_view> MnemonicEnums;

    static std::string  type_name(lex::type::T lex_type);
    static lex::type::T      type_enum(const std::string& lex_type_name);
};


} // namespace lex
