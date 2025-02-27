//
// Created by oldlonecoder on 8/17/24.
//

//#ifndef NODE_H
//#define NODE_H
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

#include <obb/est/alu.h>
#include <obb/lexer/token_data.h>
#include <obb/logbook.h>
#include <obb/object.h>


namespace obb::est
{




class OBBESTLIB node : public obb::object
{
protected:
    alu*    _a_ {nullptr};  ///< alu / playing the role of accumulator for this node.
    node*   _op_{nullptr}; ///< parent node operator
    node*   _l_ {nullptr}; ///< left-hand-side operand
    node*   _r_ {nullptr}; ///< right-hand-side operand
    lex_token* _token_{nullptr};
    friend class bloc;
    friend class expr;
    friend class variable;
    struct OBBESTLIB storage_type
    {
        integers::u8 lv    : 1; ///< 0 = rvalue non-assignable (such as const,leaf). 1= left value; assignable.
        integers::u8 acc   : 1; ///< 1 = this node owns its acc storage - so will delete it in the destructor.
        integers::u8 leave : 1; ///< 1 = leave flag because this node is a return/exit/exception/interrupt/break/continue node.
        integers::u8 ss    : 1; ///< 1 = static storage.
        integers::u8 ref   : 1; ///< 1 = cannot be deleted by the parent's destructor.
        // ...
    }mem = { 0,0,0,0,0 }; ///< Storage types of this node.
public:
    node();
    node(obb::object* a_parent_scope);
    node(obb::object* a_parent_scope, lex_token* a_token, alu* _a=nullptr);

    virtual ~node();

    inline alu&            operator*() const {return *_a_;}
    inline lex_token& token() const {return *_token_;}
    inline alu*            operator->() const {return _a_;}

    virtual alu JSR();
    using maker = std::function<node * (lex_token *)>;
    std::string type_name() const;

    static void syntax_error(node* e);
    static void make_error(rem::cc ErrCode, node* source_node, node* input_node);
    static void warning(node* );
    void        header(node* input_node, std::source_location&& Loc) const;

    node* tree_input(node* parent_bloc, lex_token* token, node::maker mk= nullptr);
    node* tree_input_binary(node* a);
    node* close_pair(node* a);
    node* collapse_par_pair(node* a);
    node* close_tree();
    node* tree_root(bool skip_syntax);
    // (fr) D&egrave;s la phase d'association, on peut d&eacute;j&agrave; conna&icirc;tre le mouvement:
    //  - en validant l'appel de la fonction
    //  - en r&eacute;-associant le nouveau node en se servant de la table move_tbl;
    // -----------------------------------------------------------------------------------------------

    static node* tree_begin(node* ParentObj, lex_token* a_token, node::maker node_maker= nullptr);
    node* set_to_right_operand(node* in_rhs);
    node* set_to_left_operand(node* in_lhs);
    node* set_operand_to_right(node* a);

    [[nodiscard]] std::string attribute() const { return _token_ ? std::string(_token_->text().data()) : "nullptr"; }
    alu value() const { return _a_ ? *_a_ : alu(0.0f); }

    std::string trace_connect_postfix_operands(node* x);
    std::string trace_connect_binary_operands(node* x);
#pragma region GRAPHVIZ_DOT
    static void dot_tree_start(obb::string& a_out, const obb::string& Title);
    static void dot_node(node* A, obb::string& a_out);
    static void dot_null_node(node*, int, obb::string&);
    static void dot_tree(node* a_root, obb::string& a_out);
    static void dot_tree_close(obb::string& a_out);
    void dot_attr(obb::string& a_out);
#pragma endregion GRAPHVIZ_DOT

private:

    using input_fn = node*(node::*)(node*);
    static std::stack<node*> s_pars;
    static size_t push_par(node* a);
    static node* pop_par();

    using input_table_t = std::vector<std::pair<std::pair<lex::type::T, lex::type::T>, std::string>>;
    using move_table_t = std::vector< std::pair< std::pair< lex::type::T, lex::type::T >, node::input_fn > >;
    static input_table_t input_tbl;
    static move_table_t move_tbl;
    static void build_move_table();

    using operator_fn = alu(node::*)();
    using operators_table = std::map<lex::mnemonic::T, node::operator_fn>;
    static operators_table s_operator_table;
    operator_fn            _op_fn_{nullptr};
    static node::input_fn  match(node* in_lhs, node* in_rhs);
    // --------------------------------------------------Arithmetic Operations BEGIN--------------------------------------------
#pragma region operations
    virtual alu  LeftShift();
    virtual alu  Radical();
    virtual alu  Exponent();
    virtual alu  RightShift();
    virtual alu  Decr();
    virtual alu  Incr();
    virtual alu  AssignAdd();
    virtual alu  AssignSub();
    virtual alu  AssignMul();
    virtual alu  AssignDiv();
    virtual alu  AssignMod();
    virtual alu  AssignAnd();
    virtual alu  AssignOr();
    virtual alu  AssignXor();
    virtual alu  AssignX1();
    virtual alu  AssignLShift();
    virtual alu  AssignRShift();
    virtual alu  Leq();
    virtual alu  Geq();
    virtual alu  Eq();
    virtual alu  Neq();
    virtual alu  Add();
    virtual alu  Sub();
    virtual alu  Mul();
    virtual alu  Modulo();
    virtual alu  LessThan();
    virtual alu  GreaterThan();
    virtual alu  Assign();
    virtual alu  BinAnd();
    virtual alu  BinOr();
    virtual alu  BitXor();
    virtual alu  X1();
    virtual alu  X2();
    virtual alu  BitNot();
    virtual alu  BoolAnd();
    virtual alu  BoolOr();
    virtual alu  Division();
    virtual alu  Factorial();
    virtual alu  Positive();
    virtual alu  Negative();
    virtual alu  KPi();
    virtual alu  KCos();
    virtual alu  KAcos();
    virtual alu  KTan();
    virtual alu  KAtan();
    virtual alu  KSin();
    virtual alu  KAsin();
    virtual alu  KNumber();
    virtual alu  KU8();
    virtual alu  KU16();
    virtual alu  KU32();
    virtual alu  KU64();
    virtual alu  KI8();
    virtual alu  KI16();
    virtual alu  KI32();
    virtual alu  KI64();
    virtual alu  KReal();
    virtual alu  KString();

#pragma endregion operations
    // --------------------------------------------------Arithmetic Operations END--------------------------------------------
};

} // est

//#endif //NODE_H
