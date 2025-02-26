//
// Created by oldlonecoder on 8/18/24.
//

//#ifndef BLOC_H
//#define BLOC_H
/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/


#pragma once
#include "lus/est/variable.h"

namespace lus::est
{

class LUSESTLIB bloc : public node
{

public:
    using list = std::vector<bloc*>;
protected:
    //node::list* m_operators{nullptr};
    variable::list* _variables_{nullptr};

    node* _root_{nullptr};
    node::list*    _instructions_{nullptr};

    void add_local_variable(variable* v);

public:
    bloc()=default;
    bloc(const bloc &) = delete;
    bloc(bloc &&) = delete;
    bloc(bloc* a_parent_bloc, const std::string a_bloc_id, lex_token* a_token = nullptr, alu* a_alu=nullptr);
    ~bloc() override;

    // no copy/assign
    bloc & operator=(const bloc &) = delete;
    bloc & operator=(bloc &&)      = delete;
    bloc & operator=(const bloc &&) = delete;

    alu JSR() override;
    const variable::list& variables();
    variable* query_variable(lex_token* a_token);
    node*     append_instruction(node* _i_);
    virtual const char* source_code(){ return "lus::est::bloc: re-implement in derived interpreter"; }

};



} // est

//#endif //BLOC_H
