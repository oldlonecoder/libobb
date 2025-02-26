//
// Created by oldlonecoder on 8/22/24.
//

#include <lus/lexer/lexer_types.h>
#include <lus/string.h>

namespace lus
{


std::map<lex::type::T,     const char*> lexer_component::type_enums
{
    {lex::type::Null,         "Null"},
    {lex::type::Number,       "Number"},
    {lex::type::Text,         "Text"},
    {lex::type::VoidPtr,      "VoidPtr"},
    {lex::type::Any,          "Any"},
    {lex::type::Leaf,         "Leaf"},
    {lex::type::Sign,         "Signed"},
    {lex::type::I8,           "I8"},
    {lex::type::I16,          "I16"},
    {lex::type::I32,          "I32"},
    {lex::type::I64,          "I64"},
    {lex::type::U8,           "U8"},
    {lex::type::U16,          "U16"},
    {lex::type::U32,          "U32"},
    {lex::type::U64,          "U64"},
    {lex::type::Float,        "Float"},
    {lex::type::Var,          "Var"},
    {lex::type::Bloc,         "Bloc"},
    {lex::type::Pipe,         "Pipe"},
    {lex::type::Keyword,      "Keyword"},
    {lex::type::Unary,        "Unary"},
    {lex::type::Prefix,       "Prefix"},
    {lex::type::Postfix,      "Postfix"},
    {lex::type::Operator,     "Operator"},
    {lex::type::Binary,       "Binary"},
    {lex::type::Function,     "Function"},
    {lex::type::FunctionPtr,  "FunctionPtr"},
    {lex::type::Object,       "Object"},
    {lex::type::Pointer,      "Pointer"},
    {lex::type::Type,         "Type"},
    {lex::type::Id,           "Id"},
    {lex::type::Ref,          "Ref"},
    {lex::type::Punc,         "Punc"},
    {lex::type::Assign,       "Assign"},
    {lex::type::Bool,         "Bool"},
    {lex::type::Hex,          "Hex"},
    {lex::type::BinFormat,    "BinFormat"},
    {lex::type::OctalFormat,  "OctalFormat"},
    {lex::type::F32,          "F32"},
    {lex::type::F64,          "F64"},
    {lex::type::F128,         "F128"},
    {lex::type::OpenPair,     "OpenPair"},
    {lex::type::ClosePair,    "ClosePair"},
    {lex::type::Static,       "Static"},
    {lex::type::Const,        "Const"},
    {lex::type::Integer,      "Integer"},
    {lex::type::Unsigned,     "Unsigned"},
    {lex::type::LineComment,   "LineComment"},
    {lex::type::BlocComment,   "BlocComment"},
    {lex::type::Literal,      "Literal"}
};



//std::map<Mnemonic::T, std::string_view> Component::MnemonicEnums
//{
//    {Mnemonic::Null,             Lexem::Null},
//    {Mnemonic::LeftShift,        Lexem::LeftShift},
//    {Mnemonic::Radical,          Lexem::Radical},
//    {Mnemonic::Exponent,         Lexem::Exponent},
//    {Mnemonic::RightShift,       Lexem::RightShift},
//    {Mnemonic::Indirection,      Lexem::Indirection},
//    {Mnemonic::Deref,            Lexem::Deref},
//    {Mnemonic::Decr,             Lexem::Decr},
//    {Mnemonic::Incr,             Lexem::Incr},
//    {Mnemonic::AssignAdd,        Lexem::AssignAdd},
//    {Mnemonic::AssignSub,        Lexem::AssignSub},
//    {Mnemonic::AssignMul,        Lexem::AssignMul},
//    {Mnemonic::AssignDiv,        Lexem::AssignDiv},
//    {Mnemonic::AssignMod,        Lexem::AssignMod},
//    {Mnemonic::AssignAnd,        Lexem::AssignAnd},
//    {Mnemonic::AssignOr,         Lexem::AssignOr},
//    {Mnemonic::AssignXor,        Lexem::AssignXor},
//    {Mnemonic::AssignC1,         Lexem::AssignC1},
//    {Mnemonic::AssignLeftShift,  Lexem::AssignLShift},
//    {Mnemonic::AssignRightShift, Lexem::AssignRShift},
//    {Mnemonic::LessEq,           Lexem::LessEqual},
//    {Mnemonic::GreaterEq,        Lexem::GreaterEqual},
//    {Mnemonic::Equal,            Lexem::Equal},
//    {Mnemonic::NotEqual,         Lexem::NotEqual},
//    {Mnemonic::Add,              Lexem::Addition},
//    {Mnemonic::Sub,              Lexem::Sub},
//    {Mnemonic::Positive,         Lexem::Positive},
//    {Mnemonic::Negative,         Lexem::Negative},
//    {Mnemonic::Mul,              Lexem::Multiply},
//    {Mnemonic::Indirection,      Lexem::Indirection},
//    {Mnemonic::CommentCpp,       Lexem::CommentCpp},
//    {Mnemonic::Modulo,           Lexem::Modulo},
//    {Mnemonic::LessThan,         Lexem::LessThan},
//    {Mnemonic::GreaterThan,      Lexem::GreaterThan},
//    {Mnemonic::Assign,           Lexem::Assign},
//    {Mnemonic::BinaryAnd,        Lexem::BinaryAnd},
//    {Mnemonic::BinaryOr,         Lexem::BinaryOr},
//    {Mnemonic::BinaryXor,        Lexem::Xor},
//    {Mnemonic::C1,               Lexem::C1},// complement a 1
//    {Mnemonic::C2,               Lexem::C2},
//    {Mnemonic::BinaryNot,        Lexem::Not},   //
//    {Mnemonic::LogicalAnd,       Lexem::BoolAnd},
//    {Mnemonic::LogicalOr,        Lexem::BoolOr},
//    {Mnemonic::OpenAbsOp,        Lexem::AbsBegin},
//    {Mnemonic::CloseAbsOp,       Lexem::AbsEnd},
//    {Mnemonic::OpenPar,          Lexem::OpenPar},
//    {Mnemonic::ClosePar,         Lexem::ClosePar},
//    {Mnemonic::Openindex,        Lexem::OpenIndex},
//    {Mnemonic::Closeindex,       Lexem::CloseIndex},
//    {Mnemonic::Openbrace,        Lexem::BraceBegin},
//    {Mnemonic::Closebrace,       Lexem::BraceEnd},
//    {Mnemonic::BeginComment,     Lexem::CommentBegin},
//    {Mnemonic::EndComment,       Lexem::CommentEnd},
//    {Mnemonic::Div,              Lexem::Division},
//    {Mnemonic::Comma,            Lexem::Comma},
//    {Mnemonic::Scope,            Lexem::Scope},
//    {Mnemonic::Semicolon,        Lexem::Semicolon},
//    {Mnemonic::Colon,            Lexem::Colon},
//    {Mnemonic::Range,            Lexem::Range},
//    {Mnemonic::Factorial,        Lexem::Factorial},
//    {Mnemonic::Positive,         Lexem::Positive},
//    {Mnemonic::Negative,         Lexem::Negative},
//    {Mnemonic::Squote,           Lexem::Squote},
//    {Mnemonic::Dquote,           Lexem::Dquote},
//    {Mnemonic::Ternary,          Lexem::Ternary},
//    {Mnemonic::Hash,             Lexem::Hash},
//    {Mnemonic::Eos,              Lexem::Eos},
//    {Mnemonic::Dot,              Lexem::Dot},
//    {Mnemonic::Return,           Lexem::Return},
//    {Mnemonic::If,               Lexem::If},
//    {Mnemonic::Pi,               Lexem::Pi},
//    {Mnemonic::Number,           Lexem::Number},
//    {Mnemonic::U8,               Lexem::U8},
//    {Mnemonic::U16,              Lexem::U16},
//    {Mnemonic::U32,              Lexem::U32},
//    {Mnemonic::U64,              Lexem::U64},
//    {Mnemonic::I8,               Lexem::I8},
//    {Mnemonic::I16,              Lexem::I16},
//    {Mnemonic::I32,              Lexem::I32},
//    {Mnemonic::I64,              Lexem::I64},
//    {Mnemonic::Float,            Lexem::Float}, // Important: F32 : float; F64: double; F128: long double;
//    {Mnemonic::String,           Lexem::String},
//    {Mnemonic::Then,             Lexem::Then},
//    {Mnemonic::Else,             Lexem::Else},
//    {Mnemonic::Const,            Lexem::Const},
//    {Mnemonic::Include,          Lexem::Include},
//    {Mnemonic::Amu,              Lexem::Amu},
//    {Mnemonic::At,               Lexem::At},
//    {Mnemonic::Prime,            Lexem::Prime},
//    {Mnemonic::Do,               Lexem::Do},
//    {Mnemonic::While,            Lexem::While},
//    {Mnemonic::For,              Lexem::For},
//    {Mnemonic::Until,            Lexem::Until},
//    {Mnemonic::Repeat,           Lexem::Repeat},
//    {Mnemonic::Switch,           Lexem::Switch},
//    {Mnemonic::Case,             Lexem::Case},
//    {Mnemonic::Type,             Lexem::Type},
//    {Mnemonic::LowHex,           Lexem::LowHex},
//    {Mnemonic::UpHex,            Lexem::UpHex},
//    {Mnemonic::Cosinus,          Lexem::Cosinus},
//    {Mnemonic::ArcCosinus,       Lexem::ArcCosinus},
//    {Mnemonic::Tangent,          Lexem::Tangent},
//    {Mnemonic::ArcTangent,       Lexem::ArcTangent},
//    {Mnemonic::Sinus,            Lexem::Sinus},
//    {Mnemonic::ArcSinus,         Lexem::ArcSinus},
//    {Mnemonic::Object,           Lexem::Object},
//    {Mnemonic::Static,           Lexem::Static},
//    {Mnemonic::This,             Lexem::This},
//    {Mnemonic::Unshadow,         Lexem::Unshadow},// Take the address of the local var instance identifier, from the first parent bloc the var is declared instead.
//    {Mnemonic::Try,              Lexem::Try},
//    {Mnemonic::Catch,            Lexem::Catch},
//    {Mnemonic::Throw,            Lexem::Throw},
//    {Mnemonic::LineComment,      Lexem::LineComment},
//    {Mnemonic::BlocComment,      Lexem::BlocComment}
//};


std::string lexer_component::type_name(lex::type::T lexem_type)
{
    std::string text;
    lex::type::T TypeBits = lexem_type;
    //int                a, c, b;
    for(const auto &T: lexer_component::type_enums)
    {
        if(!TypeBits)
            break;

        if(T.first & TypeBits)
        {
            text += T.second;
            TypeBits &= ~T.first;  // Remove the Bit from the "Sem" field.
            if(TypeBits)
                text += ',';
        }
    }
    if(text.empty())
        text += "Null";
    return text;
}

lex::type::T lexer_component::type_enum(const std::string &named_type)
{
    lus::string str = named_type;
    lus::string::word::list list;
    lex::type::T tmap = 0;

    auto count = str.words(list, false,":");

    if(!count) return lex::type::Null;
    for(auto S: list)
    {
        for(auto const& [k,v] : lexer_component::type_enums)
        {
            if(std::strcmp(v, (*S).c_str()) == 0) tmap |= k;
        }
    }
    return tmap;
}




} // lex
