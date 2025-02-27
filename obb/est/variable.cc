//
// Created by oldlonecoder on 8/19/24.
//

#include <obb/est/variable.h>

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


//#pragma once




namespace obb::est {
variable::variable(node* a_parent_node, lex_token* a_token, alu* a_alu):node(a_parent_node, a_token, a_alu)
{
    _token_->sem |= lex::type::Var;
    set_id(std::string(_token_->text()));
}


alu variable::pop()
{
    if(_stack_.empty()) 
    {
        book::warning() << rem::cc::rejected << "-> stack is empty; using current alu::value." << book::eol;
        return *_a_;
    }
    *_a_ = _stack_.top();
    _stack_.pop();
    return *_a_;
}

void variable::push()
{
    _stack_.push(*_a_);
}

} // est
