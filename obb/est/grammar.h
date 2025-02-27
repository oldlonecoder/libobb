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


#include "obb/lexer/lexer.h"
//#include <obb/lexer/token_data.h>
#include <obb/glyphes.h>
#include <obb/string.h>
#include <obb/colors.h>
#include <obb/est/export.h>

//#include "obb/lexer/tokens_table.h"

/*

std::string grammar_text = R"(
unit               : 'Unit' Id ';'.
stmts              : +statement.
statement          : ';' | instruction | assignstmt ';'| declvar ';'| #expression ';'| #var_id ';'.
assignstmt         : declvar Assign #expression | #var_id Assign #expression.
declvar            : *typename #newvar.
funcsig            : *typename function_id '(' *params ')'.
declfunc           : funcsig ';'| funcsig statement ';' | funcsig bloc.
paramseq           : ',' param.
param              : *typename Id.
function_call      : function_id '(' Args ')' | objcfncall.
params             : param *+paramseq.
objcarg            : Id ':' #expression.
arg                : objcarg | #expression.
argseq             : ',' arg.
Args               : arg *+argseq.
typename           : *'static' ?'i8' ?'u8' ?'i16' ?'u16' ?'i32' ?'u32' ?'i64' ?'u64' ?'real' ?'number' ?'string' ?#objectid.
instruction        : ?'if' ?'then'  ?'switch' ?'case' ?'for' ?'while' ?'repeat' ?'until' ?'do' ?'return'.
if                 : 'if' condexpr ifbody | 'if' '(' condexpr ')' ifbody.
bloc               :  '{' stmts '}'.
truebloc           : *'then' bloc | *'then' statement.
elsebloc           : 'else' bloc | 'else' statement.
ifbody             : truebloc *elsebloc.
condexpr           : assignstmt | #expression.
function_id        : *'::' #functionid | #objectid '::' #functionid | #obj_instance '.' #functionid.
objcfncall         : '[' function_id  *Args ']'.

)";




*/

namespace obb::est
{

using namespace integers;

class LUSESTLIB grammar
{
public:

    static auto constexpr OPTIONAL      = '*';
    static auto constexpr REPEAT        = '+';
    static auto constexpr ONEOF         = '?';
    static auto constexpr EXCLUDE       = '~';
    static auto constexpr DIRECTIVE     = '#';
    static auto constexpr REJECTED      = '!';



    struct LUSESTLIB rule;
    struct LUSESTLIB props
    {
        u8 z :1; ///< zero or more := optional; '*'
        u8 r :1; ///< repeat := '+' 
        u8 l :1; ///< one of := '?'
        u8 x :1; ///< exclude := '~'
        u8 e :1; ///< directive := '#' , empty rule for the parsers to handle. (ex.: ' #expression ')
        u8 s :1; ///< state : 1 := default accepted | 1 := rejected,unset 


        props() : z(0), r(0), l(0), x(0), e(0), s(0) {}
        props& operator=(props&&) = default;
        props& operator=(const props&) = default;
        props(const props&) = default;
        props(props&&) = default;

        props& operator |(props const& _)
        {
            *this = _;
            s = 1;
            return *this;
        }


        // prefix bit assign operators 
        //--------------------------------------------------------------------------------
        /*!
        * \brief operator *() : zero or more := optional; '*'
        */
        props& operator *()
        {
            z = 1;
            return *this;
        }

        /*!
        * \brief operator +() : repeat := '+'
        */
        props& operator +()
        {
            r = 1;
            return *this;
        }


        /**
            * @brief operator ~ : exclude element. '~'
         * 
         * @return props& 
         */
        props& operator ~()
        {
            x = 1;
            return *this;
        }

        /*!
        * \brief operator ?() : one of element from the list 
         */
        props& operator-()
        {
            l = 1;
            return *this;
        }


        /*!
        * \brief operator !() : parsers to handle := '#'
         */
        props& operator!()
        {
            e = 1;
            return *this;
        }

        void reset()
        {
            z = 0;
            r = 0;
            l = 0;
            x = 0;
            e = 0;
            s = 0;
        }

        std::string to_string() const;
    };


    struct LUSESTLIB term 
    {
        grammar::props _props_;
        enum class type 
        {
            rule_type = 0, ///< this term is an (sub-)rule.
            semantic_type = 1, ///< this term is a semantic lexical token.
            mnemonic_type = 2, ///< this term is an explicit mnemonic.
            unknown_type = 3  ///< this term is an unknown or being parsed.
        };

        term::type _type_{term::type::unknown_type};

        union store 
        {
            grammar::rule* _rule_;
            lex::type::T   _semantic_;
            lex::mnemonic::T _mnemonic_;

        } _store_{nullptr};



        using list = std::vector<grammar::term>;
        using iterator = list::iterator;
        using const_iterator = list::const_iterator;


        term() = default;
        term(const term&) = default;
        term(term&&) noexcept = default;
        term& operator=(const term&) = default;
        term& operator=(term&&) noexcept = default;

        term(grammar::rule* _rule_) : _type_(term::type::rule_type)
        {
            _store_._rule_ = _rule_;
        }

        term(lex_token const& _token) : _type_(term::type::mnemonic_type)
        {
            _store_._semantic_ = _token.m;
        }


        term(lex::type::T _semantic_) : _type_(term::type::semantic_type)
        {
            _store_._semantic_ = _semantic_;
        }

        term(lex::mnemonic::T _mnemonic_) : _type_(term::type::mnemonic_type)
        {
            _store_._mnemonic_ = _mnemonic_;
        }

        term& operator=(grammar::rule* _rule_)
        {
            _type_ = term::type::rule_type;
            _store_._rule_ = _rule_;
            return *this;
        }

        term& operator=(lex::type::T _semantic_)
        {
            _type_ = term::type::semantic_type;
            _store_._semantic_ = _semantic_;
            return *this;
        }

        term& operator=(lex::mnemonic::T _mnemonic_)
        {
            _type_ = term::type::mnemonic_type;
            _store_._mnemonic_ = _mnemonic_;
            return *this;
        }

        bool operator==(const term& _term_) const
        {

            if((_type_ != _term_._type_) || (_type_ == grammar::term::type::unknown_type)) return false;
            switch(_type_)
            {
                case term::type::rule_type:
                    return _store_._rule_ == _term_._store_._rule_;
                case term::type::semantic_type:
                    return _store_._semantic_ & _term_._store_._semantic_;
                case term::type::mnemonic_type:
                    return _store_._mnemonic_ == _term_._store_._mnemonic_;
                default:
                    return false;
            }
        }

        bool operator == (lex_token const& _token) const
        {
            return (_store_._semantic_ & _token.sem) || (_token.m == _store_._mnemonic_);
        }


        bool operator!=(const term& _term_) const
        {
            return !(*this == _term_);
        }

        operator bool() const
        {
            return _type_ != term::type::unknown_type;
        }

        term& operator +()
        {
            +_props_;
            return *this;
        }

        term& operator *()
        {
            *_props_;
            return *this;
        }

        term& operator ~()
        {
            ~_props_;
            return *this;
        }

        term& operator -()
        {
            -_props_;
            return *this;
        }

        term& operator !()
        {
            !_props_;
            return *this;
        }

        void reset()
        {
            _props_.reset();
        }

        bool is_rule() const
        {
            return _type_ == term::type::rule_type;
        }

        bool is_semantic() const
        {
            return _type_ == term::type::semantic_type;
        }
        
        bool is_mnemonic() const
        {
            return _type_ == term::type::mnemonic_type;
        }

        std::string to_string(lexer::config_data& _data) const;
    };


    struct LUSESTLIB term_sequence  
    {
        term::list terms;
        term::iterator index{terms.begin()};

        using list = std::vector<grammar::term_sequence>;
        using iterator = list::iterator;
        using const_iterator = list::const_iterator;


        term_sequence() = default;
        term_sequence(const term_sequence&) = default;
        term_sequence(term_sequence&&) noexcept = default;
        term_sequence& operator=(const term_sequence&) = default;
        term_sequence& operator=(term_sequence&&) noexcept = default;

        term_sequence(const term::list& _terms_) : terms(_terms_) {}
        term_sequence(term::list&& _terms) noexcept : terms(std::move(_terms)) {}

        term_sequence& operator=(const term::list& _terms)
        {
            terms = _terms;
            return *this;
        }


        auto cbegin() { return terms.cbegin(); }
        auto cend() { return terms.cend(); }

        term_sequence& operator<<(const term& _term_)
        {
            terms.push_back(_term_);
            index = terms.end();
            --index;
            return *this;
        }

        term_sequence& operator<<(term&& _term_)
        {
            terms.push_back(std::move(_term_));
            index = terms.end();
            --index;
            return *this;
        }

        term_sequence& operator<<(lex::type::T _type_)
        {
            terms.emplace_back(_type_);
            index = terms.end();
            --index;
            return *this;
        }

        term_sequence& operator<<(lex::mnemonic::T _mnemonic_)
        {
            terms.emplace_back(_mnemonic_);
            index = terms.end();
            --index;
            return *this;
        }

        term_sequence& operator<<(grammar::rule* _rule_)
        {
            terms.emplace_back(_rule_);
            return *this;
        }

        term_sequence& operator<<(lex_token const &_token)
        {
            terms.emplace_back(_token);
            return *this;
        }

        bool empty() const { return terms.empty(); }


        std::string to_string(lexer::config_data& _data) const;

    };


    struct LUSESTLIB rule 
    {
        std::string name{};
        term_sequence::list sequences{};
        using list = std::vector<grammar::rule*>;

        using iterator = list::iterator;
        using const_iterator = list::const_iterator;

        grammar::props properties; ///< Propagation to the terms.
        term_sequence::const_iterator citerator{sequences.cbegin()};
        term_sequence::iterator index{sequences.begin()};




        rule() = default;
        rule(const std::string& _rname_) : name(_rname_) {}
        


        std::string to_string() const;

        rule& new_sequence();
        rule& operator | (rule* _rule);
        rule& operator | (lex::type::T _type_);
        rule& operator | (lex::mnemonic::T _mnemonic_);



        term_sequence::const_iterator cbegin()
        {
            return citerator;
        }

        term_sequence::const_iterator cend()
        {
            return sequences.cend();
        }
        std::string to_string(lexer::config_data& _data) const;

    };

    std::string _name_{};
    lexer::config_data _config_data_{};
    token_table _token_table_{};

public:
    grammar();
    ~grammar()=default;

    grammar(const std::string& _name, lexer::config_data _config_data);

    rem::cc build(const std::string& _name);


};


}
