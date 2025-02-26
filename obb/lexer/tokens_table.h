//
// Created by oldlonecoder on 24-01-27.
//

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
#include <lus/lexer/token_data.h>

namespace lus
{

class LUSLEXERLIB  token_table
{
    
protected:
    lex_token::list ref_table;
    lex_token::list prod_table;
    friend class lexer;
    std::string    _name_{"Default Common token_table"};



public:

    using mnemonic_colours = std::map<lex::mnemonic::T, color::code>;
    using type_colours = std::map<lex::type::T, color::code>;

    token_table()= default;

    virtual ~token_table();

    lex_token scan( const char* C);
    lex_token scan( lex::mnemonic::T _m) const;
    lex_token operator[]( lex::mnemonic::T _m) const;

    [[maybe_unused]] virtual size_t set_reference_table();
    lex_token::list&                reference_table() { return ref_table; }
    lex_token::list&                production_table() { return  prod_table; }
    token_table&                    operator << (lex_token&);
    std::size_t                     count() { return prod_table.size(); }
    bool                            empty() { return prod_table.empty(); }
    void                            dump_reference_table() const;
    void                            dump_production_table();
    lex_token const&                get(std::string_view);
    lex_token const&                get(lex::mnemonic::T);
    std::string&                    name() { return _name_; }
protected:
    static mnemonic_colours _static_mnemonic_colours_table_;
    static type_colours _static_type_colours_table_;
//    static size_t AddMnemonicsComponentFromThisTable(const lex_token::Array & Table);
//    static size_t AddMnemonicComponent(std::string_view Lexeme, Mnemonic::T Num);
};








// class LEXER_API ArithmeticLexemes : public token_table
// {
// public:

//     [[maybe_unused]] virtual size_t set_reference_table();
// };








} // ULexer
