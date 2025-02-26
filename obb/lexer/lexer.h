//
// Created by oldlonecoder on 24-03-08.
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

#include <lus/lexer/tokens_table.h>
#include <lus/lexer/sscan.h>

//#ifndef LEXER_LEXER_H
//#define LEXER_LEXER_H

namespace lus
{

class LUSLEXERLIB lexer
{
public:

    struct LUSLEXERLIB config_data
    {
        std::string_view text{};
        token_table*      production{nullptr};
    };
    config_data& config() { return m_config; }

    lexer() = default;
    virtual ~lexer() = default;

    virtual rem::cc exec();




protected:
    lus::sscan scanner{};
    virtual rem::cc loop();
    rem::cc state{rem::cc::ok};
    void push_token(lex_token&);


    void update_token_location(lex_token&);
    rem::cc tokenize(lex_token);

    config_data m_config;

    virtual rem::cc tokenize_identifier    (lex_token &);
    virtual rem::cc tokenize_binary_operator(lex_token&);
    virtual rem::cc tokenize_default       (lex_token&);
    virtual rem::cc tokenize_unary_operator (lex_token&);
    virtual rem::cc tokenize_punctuation   (lex_token&);
    virtual rem::cc tokenize_keyword       (lex_token&);
    virtual rem::cc tokenize_string        (lex_token&);
    virtual rem::cc tokenize_sign_prefix    (lex_token&);
    virtual rem::cc tokenize_prefix        (lex_token&);
    virtual rem::cc tokenize_postfix       (lex_token&);
    virtual rem::cc tokenize_cpp_comment    (lex_token&);
    virtual rem::cc tokenize_comment_bloc   (lex_token&);
    virtual rem::cc tokenize_numeric       (lex_token&);

    lex_token::list& production();


};

} // lex

//#endif //LEXER_LEXER_H
