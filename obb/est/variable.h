//
// Created by oldlonecoder on 8/19/24.
//

//#ifndef VARIABLE_H
//#define VARIABLE_H
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
#include <obb/est/node.h>
#include <stack>

namespace obb::est {

class LUSESTLIB variable : public node
{
    std::stack<alu> _stack_{};

public:

    using list = std::vector<variable*>;

    variable() = default;
    variable(node* a_parent_node, lex_token* a_node, alu* a_alu);

    ~variable() override=default;

    alu JSR() override { return *_a_;};
protected:
    void push();
    alu  pop();

};

} // est

//#endif //VARIABLE_H
