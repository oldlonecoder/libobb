//
// Created by oldlonecoder on 8/17/24.
//

#include <lus/est/node.h>
#include <lus/est/expression.h>
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




namespace lus::est {


static node* _global_root_bloc{nullptr};


std::stack<node*> node::s_pars{};
std::size_t node::push_par(node* a)
{
    node::s_pars.push(a);
    return node::s_pars.size();
}


node* node::pop_par()
{
    if(node::s_pars.empty()) return nullptr;
    node* n = node::s_pars.top();
    node::s_pars.pop();
    return n;
}

//node* node::get_global_root() { return node::{lex::type::binary,     lex::type::open_pair},  &node::set_right_global_root_bloc; }


#define deg2rad(_node) (((_node)->_a_->v.d*3.1415) / 180)
constexpr auto _PI_ = 3.14159265358979323846;
// M_PI ?



// void node::// discard()
// {
//     for (auto x : node::node_gc)
//         if (this == x) return;

//     node::node_gc.push_back(this);
//     lhs = rhs = op = nullptr; // Make sure we do not accidently reuse this;
// }



    // Primary arithmetic supported operators table:
node::operators_table node::s_operator_table={
    {lex::mnemonic::LeftShift,           &node::LeftShift},
    {lex::mnemonic::Radical,             &node::Radical},
    {lex::mnemonic::Exponent,            &node::Exponent},
    {lex::mnemonic::RightShift,          &node::RightShift},
    {lex::mnemonic::Decr,                &node::Decr},
    {lex::mnemonic::Incr,                &node::Incr},
    {lex::mnemonic::AssignAdd,           &node::AssignAdd},
    {lex::mnemonic::AssignSub,           &node::AssignSub},
    {lex::mnemonic::AssignMul,           &node::AssignMul},
    {lex::mnemonic::AssignDiv,           &node::AssignDiv},
    {lex::mnemonic::AssignMod,           &node::AssignMod},
    {lex::mnemonic::AssignAnd,           &node::AssignAnd},
    {lex::mnemonic::AssignOr,            &node::AssignOr},
    {lex::mnemonic::AssignXor,           &node::AssignXor},
    {lex::mnemonic::AssignC1,            &node::AssignX1},
    {lex::mnemonic::AssignLeftShift,     &node::AssignLShift},
    {lex::mnemonic::AssignRightShift,    &node::AssignRShift},
    {lex::mnemonic::LessEq,              &node::Leq},
    {lex::mnemonic::GreaterEq,           &node::Geq},
    {lex::mnemonic::Equal,               &node::Eq},
    {lex::mnemonic::NotEqual,            &node::Neq},
    {lex::mnemonic::Add,                 &node::Add},
    {lex::mnemonic::Sub,                 &node::Sub},
    {lex::mnemonic::Mul,                 &node::Mul},
    {lex::mnemonic::Modulo,              &node::Modulo},
    {lex::mnemonic::LessThan,            &node::LessThan},
    {lex::mnemonic::GreaterThan,         &node::GreaterThan},
    {lex::mnemonic::Assign,              &node::Assign},
    {lex::mnemonic::BinaryAnd,           &node::BinAnd},
    {lex::mnemonic::BinaryOr,            &node::BinOr},
    {lex::mnemonic::BinaryXor,           &node::BitXor},
    {lex::mnemonic::C1,                  &node::X1},
    {lex::mnemonic::C2,                  &node::X2},
    {lex::mnemonic::BinaryNot,           &node::BitNot},
    {lex::mnemonic::LogicalAnd,          &node::BoolAnd},
    {lex::mnemonic::LogicalOr,           &node::BoolOr},
    {lex::mnemonic::Div,                 &node::Division},
    {lex::mnemonic::Factorial,           &node::Factorial},
    {lex::mnemonic::Positive,            &node::Positive},
    {lex::mnemonic::Negative,            &node::Negative},
    {lex::mnemonic::Pi,                  &node::KPi},
    {lex::mnemonic::Cosinus,             &node::KCos},
    {lex::mnemonic::ArcCosinus,          &node::KAcos},
    {lex::mnemonic::Tangent,             &node::KTan},
    {lex::mnemonic::ArcTangent,          &node::KAtan},
    {lex::mnemonic::Sinus,               &node::KSin},
    {lex::mnemonic::ArcSinus,            &node::KAsin},
    {lex::mnemonic::Number,              &node::KNumber},
    {lex::mnemonic::U8,                  &node::KU8   },
    {lex::mnemonic::U16,                 &node::KU16  },
    {lex::mnemonic::U32,                 &node::KU32  },
    {lex::mnemonic::U64,                 &node::KU64  },
    {lex::mnemonic::I8,                  &node::KI8   },
    {lex::mnemonic::I16,                 &node::KI16  },
    {lex::mnemonic::I32,                 &node::KI32  },
    {lex::mnemonic::I64,                 &node::KI64  },
    {lex::mnemonic::Float,               &node::KReal },
    {lex::mnemonic::String,              &node::KString}
};





node::node()
{
    _a_ = new alu(0.0f);
    mem.acc = 1;
    mem.ref = 0;
}

node::node(lus::object* a_parent_scope) : lus::object(a_parent_scope, "node")
{
    _a_ = new alu;
    mem.acc = 1;
    mem.ref = 0;
}


node::~node()
{
    if (!mem.ref && mem.acc) delete _a_;
}


node::node(lus::object* a_parent_scope, lex_token* a_token, alu* _a): lus::object(a_parent_scope, a_token ? std::string(a_token->text()) : "node")
{
    _token_ = a_token;

    //journal::debug() << rem::fn::fun << "node::node => token details:[" << (t0 ? t0->Details() : "nullptr") << "]"<< rem::fn::endl ;

    if (_a != nullptr)
    {
        _a_ = _a;
        mem.acc = 0;
        mem.ref = 1;
        return;
    }

    _a_ = new alu(0.0f);
    mem.acc = 1;
    mem.ref = 0;

    if (!_token_)
        return;

    switch (_token_->prim) {
        case lex::type::Text:
            *_a_ = std::string(a_token->text()); // deep copy 'cause _alu_ is this node's alu
            return;
        case lex::type::Number:
        {
            if(_token_->sem & lex::type::Keyword)
            {
                _op_fn_ = node::s_operator_table.find(a_token->m)->second;

                if(!_op_fn_)
                    throw journal::exception() [ journal::fatal() << _token_->mark(parent<bloc>()->source_code(), false) << rem::fn::endl << "as no implementation!" ];
                return;
            }
            if (_token_->sem & lex::type::Const)
            {
                double d;
                (lus::string(a_token->text())) >> d;
                *_a_ = d;
                journal::debug() <<  " acc: " << color::yellow << (*_a_)() << journal::eol;
            }
        }
        return;
        case lex::type::Hex:
        {
            uint64_t d;
            lus::string(a_token->text()).hex(d);
            *_a_ = d;
            return;
        }
        return;
        case lex::type::Any:
        case lex::type::VoidPtr:
            *_a_ = static_cast<void *>(nullptr);
            return;
        default:

        break;
    }

    _op_fn_ = node::s_operator_table.find(a_token->m)->second;
    //journal::debug() << rem::fn::fun << " acc: '" << color::yellow << (*acc)() << color::white << "'";
}

//Util::Object::Iterator node::GetChildIterator(node* c)
//{
//    auto It = _children.TreeBegin();
//
//    for(; It != _children.end(); It++)
//    {
//        if(*It == c)
//            break;
//    }
//    return It;
//}

#pragma region JSR

// ------------------ ARITHMETIC OPERATORS IMPLEMENTATION ---------------------------------------------

alu node::JSR()
{
    //...
    try {
        //journal::debug() << rem::fn::fun << color::white << attribute() << " Value:" << color::yellow << _a_->number<uint64_t>() << rem::fn::endl << _token_->Details(true) ;
        if (_token_->is_operator())
        {
            if (_l_) *_a_ = _l_->JSR(); // Always execute the lhs ast node so we return that one if this has no rhs operand (_r_ == null).
            if (_r_) *_a_ = _r_->JSR(); // Execute the rhs ast node if applicable(not null) - It is the usual return value.

            if (_op_fn_)
                return (this->*_op_fn_)();// All operators assign _a_.
            else
                journal::warning() <<  "operator node [" << color::yellow << _token_->text() << color::reset << "] has no implementation (yet?).:\n" << _token_->mark(parent<bloc>()->source_code(), false) << journal::eol;
        }
        else
        {
            if(_op_fn_)
            {
                journal::debug() <<  " Non operator call: " <<  _token_->mark(parent<bloc>()->source_code(), false)  << journal::eol;
                return (this->*_op_fn_)();
            }

        }
        _token_->sem |= _a_->T;
    }
    catch(journal::exception& e)
    {
        journal::except() << e.what();
    }
    return *_a_;
}


//journal::Enums::Code node::AppendChild(node*c)
//{
//    auto e = GetChildIterator(c);
//    if(e != _children.end())
//        _children.push_back(c);
//    else
//        return journal::Enums::Code::Exist;
//
//    return journal::Enums::Code::Accepted;
//}


//journal::Enums::Code node::Detach(node* c)
//{
//    auto i = GetChildIterator(c);
//    if(i != _children.end())
//        _children.erase(i);
//    else
//        return journal::Enums::Code::Notexist;
//
//    return journal::Enums::Code::Accepted;
//}
//
//journal::Enums::Code node::detach()
//{
//    node* p = Parent<node>();
//    if(p)
//    {
//        p->Detach(this);
//    }
//    return journal::Enums::Code::Accepted;
//}



alu node::LeftShift()
{
    if((_l_->_token_->sem & lex::type::Float) || (_r_->_token_->sem & lex::type::Float))
    {
        *_a_ = 0.f;
        journal::warning() <<  _l_->_token_->name << " " << _token_->text() << " " << _r_->_token_->type_name() << " are incompatible" ;
    }

    *_a_ = _l_->_a_->number<uint64_t>() << _r_->_a_->number<uint64_t>();
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::Radical()
{
    *_a_ = std::pow(_l_->_a_->number<double>(), 1 / _r_->_a_->number<double>());
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::Exponent()
{
    *_a_ = std::pow(_l_->_a_->number<double>(), _r_->_a_->number<double>());
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::RightShift()
{
    *_a_ = _l_->_a_->number<uint64_t>() >> _r_->_a_->number<uint64_t>();
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Decr()
{
    *_a_ = _token_->has_type(lex::type::Prefix) ? --(*_r_->_a_) : (*_l_->_a_)--;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Incr()
{
    *_a_ = _token_->has_type(lex::type::Prefix) ? ++(*_r_->_a_) : (*_l_->_a_)++;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::AssignAdd()
{
    *_a_ = *(_l_->_a_) += *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return  *_a_;
}


alu node::AssignSub()
{
    *_a_ = *(_l_->_a_) -= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return  *_a_;
}


alu node::AssignMul()
{
    *_a_ = *(_l_->_a_) *= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::AssignDiv()
{
    *_a_ = *(_l_->_a_) /= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::AssignMod()
{
    *_a_ = *(_l_->_a_) %= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;

}
alu node::AssignAnd()
{
    *_a_ = *(_l_->_a_) &= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;

}
alu node::AssignOr()
{
    *_a_ = *(_l_->_a_) |= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;

}
alu node::AssignXor()
{
    *_a_ = *(_l_->_a_) ^= *(_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;

}
alu node::AssignX1()
{
    *_a_ = ~(*_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::AssignLShift()
{
    *_a_ = *_l_->_a_ <<= *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::AssignRShift()
{
    *_a_ = *_l_->_a_ >>= *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Leq()
{
    *_a_ = *_l_->_a_ <= *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Geq()
{
    *_a_ = *_l_->_a_ >= *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Eq()
{
    *_a_ = (*_l_->_a_) == (*_r_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Neq()
{
    *_a_ = *_l_->_a_ != *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::Add()
{
    journal::debug() <<  color::yellow << **_l_ << " " << color::cornflowerblue << _token_->text() << " " << color::yellow << **_r_ << ":";
    *_a_ = *_l_->_a_ + *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::Sub()
{
    // hack... en attendant :
    if (_token_->sem & lex::type::Sign)
        return Negative();
    journal::debug() <<  color::lime
                     << color::yellow << _l_->value()() << " " << color::cornflowerblue << attribute() << " " << color::yellow << _r_->value()() << ":";
    *_a_ = *_l_->_a_ - *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();

    return *_a_;
}
alu node::Mul()
{
    journal::debug()
        << color::yellow << _l_->attribute()
        << color::cornflowerblue << attribute()
        << color::yellow << _r_->attribute();
    *_a_ = *_l_->_a_ * *_r_->_a_;
    journal::write() << color::cornflowerblue << " => " << color::lime << (*_a_)() ;
    return *_a_;
}
alu node::Modulo()
{
    *_a_ = *_l_->_a_ % *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::LessThan()
{
    *_a_ = *_l_->_a_ < *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::GreaterThan()
{
    *_a_ = *_l_->_a_ > *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::Assign()
{
    journal::debug() << color::aquamarine3 << _l_->attribute() << color::reset << " "
                 << " " << color::lightcyan3 << attribute() << " "
                 << color::yellow << _r_->value()() <<  journal::endl;

    *_l_->_a_ = *_r_->_a_;
    *_a_ = *_r_->_a_;

    return *_a_;
}


alu node::BinAnd()
{
    *_a_ = *_l_->_a_ & *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}


alu node::BinOr()
{
    *_a_ = *_l_->_a_ | *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}


alu node::BitXor()
{
    *_a_ = *_l_->_a_ ^ *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}

alu node::X1()
{
    *_a_ = ~(*_l_->_a_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}

alu node::X2()
{
    *_a_ = ~(*_l_->_a_) + alu(1);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}


alu node::BitNot()
{
    *_a_ = !_r_->_a_->number<double>();
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}


alu node::BoolAnd()
{
    *_a_ = *_l_->_a_ && *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;
}
alu node::BoolOr()
{
    *_a_ = *_l_->_a_ || *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)()<< journal::endl;
    return *_a_;

}

alu node::Division()
{
    journal::debug() <<  color::lime
                     << color::yellow << _l_->value()()
                     << " " << color::cornflowerblue << attribute() << " "
                     << color::yellow
                 << _r_->value()() << ":" << journal::endl;

    *_a_ = *_l_->_a_ / *_r_->_a_;
    journal::debug() << color::cornflowerblue << " => " << color::lime << (*_a_)();
    return *_a_;
    //journal::debug() << color::cornflowerblue << " = " << color::lime << (*acc)();
}


alu node::Factorial()
{
    //*acc = acc->factorial(*lhs->acc);
    journal::debug() <<  color::lime << _l_->attribute()
                     << color::yellow << " " << (*_l_->_a_)() << " "
                     << color::cornflowerblue << attribute() << color::white << ":" ;

    //journal::debug() << node::trace_connect_postfix_operands(this) ;

    *_a_ = _l_->_a_->factorial();

    journal::debug() << color::cornflowerblue << " => " << color::yellow << (*_a_)();
    return *_a_;
}



alu node::Positive()
{
    if (_r_->_a_->number<double>() < 0)
        *_r_->_a_ *= -1;

    *_a_ = *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::Negative()
{
    journal::debug() <<  color::lime
                     << color::cornflowerblue << attribute()
                     << color::yellow << _r_->attribute()
        << color::white << "=" ;

    if (_r_->_a_->number<double>() > 0) // ==> a = -1;  -a = ?
        *_r_->_a_ *= -1;

    *_a_ = *_r_->_a_;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::KPi()
{
    *_a_ = alu(_PI_);
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::KCos()
{
    *_a_ = std::cos(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::KAcos()
{
    *_a_ = std::acos(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}
alu node::KTan()
{
    *_a_ = std::tan(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}


alu node::KAtan()
{
    *_a_ = std::atan(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();

    return *_a_;
}

alu node::KSin()
{
    *_a_ = std::sin(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::KAsin()
{
    *_a_ = std::asin(deg2rad(_r_));
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::KNumber()
{

    return *_a_;
}

alu node::KU8()
{
    *_a_ = _r_->_a_->number<uint64_t>() & 0xFF;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::KU16()
{
    *_a_ = _r_->_a_->number<uint64_t>() & 0xFFFF;
    journal::debug() << color::cornflowerblue << " = " << color::lime << (*_a_)();
    return *_a_;
}

alu node::KU32()
{
    *_a_ = _r_->_a_->number<uint64_t>() & 0xFFFFFFFF;
    return *_a_;
}

alu node::KU64()
{
    *_a_ = (uint64_t)(_r_->_a_->number<uint64_t>());// & 0xFFFFFFFFFFFFFFFF);
    return *_a_;
}

alu node::KI8()
{
    *_a_ = static_cast<int8_t>(_r_->_a_->number<int64_t>() & 0xFF);
    return *_a_;
}

alu node::KI16()
{
    journal::debug() <<  _r_->_token_->text();
    *_a_ = static_cast<int16_t>(_r_->_a_->number<uint64_t>() & 0xFFFF);
    return *_a_;
}

alu node::KI32()
{
    *_a_ = static_cast<int32_t>(_r_->_a_->number<uint64_t>() & 0xFFFFFFFF);
    return *_a_;
}

alu node::KI64()
{
    //*acc = (int64_t)(rhs->acc->number<int64_t>() & 0xFFFFFFFFFFFFFFFF);
    *_a_ = _r_->_a_->number<int64_t>();
    return *_a_;
}

alu node::KReal()
{
    *_a_ = _r_->_a_->number<double>();
    return *_a_;
}

alu node::KString()
{
    *_a_ = std::string(*_r_->_a_);
    return *_a_;
}


[[maybe_unused]] std::string node::type_name() const
{
    return lexer_component::type_name(_token_->prim);
}


node::input_fn node::match(node* in_lhs, node* in_rhs)
{
    for (auto [lr, fn] : node::move_tbl)
        if (auto [l, r] = lr; (in_lhs->_token_->prim & l) && (in_rhs->_token_->prim & r)) return fn;

    return nullptr;
}

#pragma endregion JSR




node::move_table_t node::move_tbl{};

void node::build_move_table()
{
    journal::message() <<  " Building the associative/move table...";
    if(!node::move_tbl.empty())
    {
        journal::error() <<  " The associative/move table is already built.";
        return;
    }
    node::move_tbl.push_back({{lex::type::OpenPair, lex::type::Leaf | lex::type::Prefix | lex::type::Binary | lex::type::Id | lex::type::Number | lex::type::Const}, &node::set_to_left_operand});
    node::move_tbl.push_back({{lex::type::Binary | lex::type::Prefix | lex::type::Sign | lex::type::Assign,  lex::type::OpenPair | lex::type::Leaf | lex::type::Prefix | lex::type::Number | lex::type::Id}, &node::set_to_right_operand});
    node::move_tbl.push_back({{lex::type::ClosePair | lex::type::Prefix | lex::type::Postfix | lex::type::Id | lex::type::Number | lex::type::Const, lex::type::ClosePair }, &node::close_pair});
    node::move_tbl.push_back({{lex::type::ClosePair, lex::type::Binary | lex::type::Postfix | lex::type::ClosePair}, &node::collapse_par_pair});
    node::move_tbl.push_back({{lex::type::Number | lex::type::Binary | lex::type::Prefix | lex::type::Postfix | lex::type::Id, lex::type::Assign | lex::type::Binary}, &node::tree_input_binary});
    node::move_tbl.push_back({{lex::type::Number | lex::type::Id, lex::type::Postfix}, &node::set_operand_to_right});
}

node::input_table_t node::input_tbl =
{
    {{lex::type::Id     | lex::type::Assign,    lex::type::Assign}, "&node::_assign"},
    {{lex::type::Number | lex::type::Const | lex::type::Postfix | lex::type::ClosePair | lex::type::Id,    lex::type::Binary}, "&node::TreeInputBinary"},
    {{lex::type::Number | lex::type::Id    | lex::type::ClosePair | lex::type::Const,    lex::type::Postfix},  "&node::_postfix"},
    {{lex::type::Binary,  lex::type::Prefix},     "&node::_prefix"},
    {{lex::type::Prefix | lex::type::Binary | lex::type::OpenPair | lex::type::Assign,    lex::type::Leaf | lex::type::Number | lex::type::OpenPair | lex::type::Id | lex::type::Prefix},  "&node::_leaf"},
    {{lex::type::Prefix | lex::type::Binary | lex::type::OpenPair,    lex::type::OpenPair},    "&node::_open_pair"},
    {{lex::type::Postfix| lex::type::Const | lex::type::Number | lex::type::Id | lex::type::OpenPair | lex::type::ClosePair,    lex::type::ClosePair}, "&node::close_pair"}
};


void node::syntax_error(node* e)
{
    throw journal::exception() [journal::syntax() << "at " << e->_token_->token_location() << rem::fn::endl << e->_token_->mark(e->parent<bloc>()->source_code(), false)] ;
}

void node::warning(node* x)
{
    journal::warning() << "at " << x->_token_->token_location() << rem::fn::endl << x->_token_->mark(x->parent<bloc>()->source_code(), false);
}




/*!
 * \brief node::TreeInput
 *
 * \note Call to this function is stricly, restricted To the Arithmetic Expression Tree/AST Build context.
 * \param parent_bloc
 * \param token
 * \param mk
 * \return new Insertion node ( or vertex? ).
 *
 * ex.: if x-1 + 12 ==  0 return 12;
 * * ex.: if a+1+b+c d = 12;
 */
node* node::tree_input(node* parent_bloc, lex_token* token, node::maker mk)
{
    for (auto& [lr, fntext] : node::input_tbl)
    {
        if (auto [l, r] = lr; (_token_->prim & l) && (token->prim & r))
        {
            journal::debug() << color::yellow
            << _token_->text() << " <- "
            << color::yellow << token->text()
            << color::reset
            << " Input TokenPtr validated: '" << color::yellow << fntext << color::reset << "'";

            ///@todo Check id tokens for function_call and other id-constructs before calling est::node::tree_input(...).

            node* a;
            if(mk)
                a = mk(token);
            else
                a  = new node(parent_bloc, token,nullptr);

            if(!a) return nullptr;
            const auto fn = node::match(this, a);
            if (!fn)
            {
                a->detach();
                delete a;
                journal::write()
                    << rem::type::syntax << ": invalid relational operands at "
                    << token->token_location()
                    << " - unexpected Token:" <<  token->details() << rem::fn::endl
                    << token->mark(parent<bloc>()->source_code(), false) << rem::fn::endl
                    << " Should ends expression syntax tree (est) construct.";
                return nullptr;
            }
            journal::write() << _token_->text() << " -> tree_input(" << token->text() << "):" << rem::fn::endl << token->mark(parent<bloc>()->source_code(), false);
            return (this->*fn)(a);
        }
    }

    journal::info() << color::white << "'" << color::yellow << _token_->text() << color::white << "'" << color::reset
                    << "::tree_input(" << color::yellow << token->text() << color::reset << ") => invalid relational operands at "
                    << token->token_location() << " - unexpected token."
                    << rem::fn::endl << token->mark(parent<bloc>()->source_code(), false) << rem::fn::endl ;
    journal::write() << _token_->details() << " || " << token->details() << rem::fn::endl << "Returning nullptr" ;
    return nullptr;
}


node* node::tree_input_binary(node* a)
{
    header(a, std::source_location::current());

    if (_token_->has_type(lex::type::Leaf))
    {
        if (a->_token_->m == lex::mnemonic::OpenPar) /* Ex.: Id <-( */
            syntax_error(a);
    }

    if (_token_->m == lex::mnemonic::OpenPar)
        return set_to_left_operand(a);

    if (_token_->has_type(lex::type::Binary))
    {
        //if (!rhs) syntax_error(a);

        if (a->_token_->d < _token_->d)
            return set_to_right_operand(a);
    }

    if (_op_) {
        const auto fn = node::match(this, a);
        if (!fn)
            node::make_error(rem::cc::unexpected, this, a);
        return (_op_->*fn)(a);

    }
    a->set_to_left_operand(this); // returns "this" - however from here, we must return { a } as the new insertion node into the tree...
    return a;
}


void node::make_error(rem::cc ErrCode, node* source_node, node* input_node)
{
    throw journal::exception()
    [
        journal::error() << source_node->attribute()
        << " TokenPtr TreeInput error: "
        << ErrCode
        << input_node->attribute()
        << rem::fn::endl
        << input_node->_token_->mark(input_node->parent<bloc>()->source_code(), false)
    ];
}

void node::header(node* input_node, std::source_location&& Loc) const
{
    journal::debug(Loc)
    << color::yellow << _token_->type_name()
    << color::grey100 << "[" << color::blueviolet << _token_->text() << color::grey100 << "] "
    << color::lightsteelblue << " <== "
    << color::yellow << input_node->_token_->type_name()
    << color::grey100 << "[" << color::blueviolet << input_node->_token_->text() << color::grey100 << "]"
    << rem::fn::endl << input_node->_token_->mark(input_node->parent<bloc>()->source_code(), false);

}






node* node::close_pair(node* a)
{
    header(a, std::source_location::current());
    const node* x = node::pop_par();
    if (!x)
    {
        throw journal::exception()
        [
            journal::except() << rem::type::syntax << "Unmatched left parenthesis:" << rem::fn::endl << a->_token_->mark(parent<bloc>()->source_code(), false)
        ];
        return nullptr;
    }
    a->_op_ = x->_op_;
    a->_l_ = x->_l_;
    if (a->_l_)
    {
        if (a->_l_->_op_)
            a->_l_->_op_ = a;
    }
    if (a->_op_)
        a->_op_->_r_ = a; // oops!!

    journal::debug()
        << "new TreeInput vertex:["
        << color::yellow
        << a->_token_->text()
        << color::reset
        << "]" << rem::fn::endl
        << a->_token_->mark(parent<bloc>()->source_code(), false);

    return a;
}


/*!
 * \brief node::collapse_par_pair
 * \param a
 * \return
 *
    \code
     [/]                  [/] <- !
    /  \                   \
   42   ) <-- !             -
       /                     \
      -                       4
       \
        4
    \endcode
 */
node* node::collapse_par_pair(node* a)
{
    header(a, std::source_location::current());
    //node* v = lhs;

    // Collapse lhs
    if(!_l_)
        throw journal::exception()[
            journal::except() << rem::type::syntax << " cannot 'collpase' parenthese sub-expr: no left-operand"
    ];


    _l_->_op_ = _op_;
    if (_op_)
    {
        _op_->_r_ = _l_;
        if(a->_token_->d < _op_->_token_->d)
        {
            return _op_->set_to_right_operand(a);
        }
    }

    // discard();

    if (_l_->_op_) {
        journal::debug()
            << color::yellow << _l_->_op_->attribute() << color::cornflowerblue
            << " <-- "
            << color::yellow << a->attribute();
        const auto p_fn = match(_l_->_op_, a);
        if (!p_fn)
            node::syntax_error(a);

        return (_l_->_op_->*p_fn)(a);
    }

    _l_->_op_ = a;
    a->_l_ = _l_;
    return a;
}

node* node::set_operand_to_right(node* a)
{
    header(a, std::source_location::current());
    if (!_op_) {
        a->_l_ = this;
        _op_ = a;
        return a;
    }
    return _op_->set_to_right_operand(a);
}



node* node::tree_begin(node* ParentObj, lex_token* a_token, node::maker node_maker)
{

    node::build_move_table();
    journal::debug() << journal::eol;
    journal::write() << color::yellow << rem::fn::endl << a_token->text();

    node* a;

    if (!a_token->flags.V)
        return nullptr;

    if(node_maker)
        a = node_maker(a_token);
    else
        a = new node(ParentObj,a_token, nullptr);
    if(!a)
        return nullptr;

    if (a->_token_->prim == lex::mnemonic::OpenPar) node::push_par(a);
    return a;
}


node* node::close_tree()
{
    header(this, std::source_location::current());

    if (_token_->m == lex::mnemonic::OpenPar)
    {
        journal::error() << " unexpected End of file." ;
        return nullptr;
    }

    if (!node::s_pars.empty())
    {
        const node* x = node::pop_par();
        journal::error() << " umatched closing parenthese from:" << rem::fn::endl << x->_token_->mark(parent<bloc>()->source_code(), false);
        return nullptr;
    }


    if (_token_->m == lex::mnemonic::ClosePar) {
        journal::debug() <<  "Closing the tree on close parenthese:";
        if (_l_)
        {
            node* x = _l_;
            journal::debug() <<  "left hand side operand: " << _l_->_token_->details() << ":" << rem::fn::endl << _l_->_token_->mark(parent<bloc>()->source_code(), false);

            _l_->_op_ = _op_;

            if (_op_)
            {
                _op_->_r_ = _l_;
                node::trace_connect_binary_operands(_op_);
            }

            // discard();
            return x->tree_root(false);
        }
    }
    return tree_root(false);
}

node* node::tree_root(const bool skip_syntax)
{
    header(this, std::source_location::current());
    //journal::debug() << rem::fn::fun << "Match tree ins from node node:" << rem::fn::endl << _token_->mark(parent<bloc>()->source_code(), false) << rem::fn::endl ;
    auto* x = this;
    node* p = x;
    do {
        x = p;
        if (!skip_syntax)
        {
            switch (x->_token_->prim) {
            case lex::type::Assign:
            case lex::type::Binary:
                if (!x->_l_)
                {
                    journal::error() << "Syntax error: binary operator has no left operand." << rem::fn::endl << x->_token_->mark(parent<bloc>()->source_code(), false);
                    return nullptr;
                }
                if (!x->_r_)
                {
                    journal::error() << "Syntax error: binary operator has no right operand." << rem::fn::endl << x->_token_->mark(parent<bloc>()->source_code(), false);
                    return nullptr;
                }
            case lex::type::Prefix:
                if (!x->_r_)
                {
                    journal::error() << "Syntax error: prefix unary operator has no (right) operand." << rem::fn::endl << x->_token_->mark(parent<bloc>()->source_code(), false);
                    return nullptr;
                }
                break;
            case lex::type::Postfix:
                if (!x->_l_)
                {
                    journal::error() << "Syntax error: postfix unary operator has no (left) operand." << rem::fn::endl << x->_token_->mark(parent<bloc>()->source_code(), false);
                    return nullptr;
                }
                break;
            default: break;
            }
        }
        p = p->_op_;
    } while (p);
    return  x;
}

node* node::set_to_right_operand(node* in_rhs)
{
    header(in_rhs, std::source_location::current());

    // Temporary hack....
    if (in_rhs->_token_->prim == lex::type::OpenPair)
        node::push_par(in_rhs);

    if (_r_) {
        /*
           this
              \
               x <- nextoken
              /
            rhs
        */
        journal::debug() <<  _token_->text() << " -> " << _r_->_token_->text()
                         << color::lime << "::tree_set_right"
                         << color::white << " <- "
                         << color::yellow << in_rhs->_token_->text();
        _r_->_op_ = in_rhs;
        in_rhs->_l_ = _r_;
    }
    _r_ = in_rhs;
    in_rhs->_op_ = this;
    if (_token_->has_type(lex::type::Binary))
    {
        journal::debug() <<  node::trace_connect_binary_operands(this);
    }
    return in_rhs;
}

node* node::set_to_left_operand(node* in_lhs)
{
    header(in_lhs, std::source_location::current());
    /*
    (; [; {   // Appliqué sur aucun autre type de token car l'appel de tree_set_left ne se fait qu'� partir de tree_input qui r�soud l'associativit�.
              /
             x < -nextoken
            /
            lhs
    */

    if (_l_) {
        //  we are supposed to be the openning par/index/bracket/bloc. So the interior will become right hand side of the parent op of this.
        _l_->_op_ = in_lhs;
        in_lhs->_l_ = _l_;
    }
    in_lhs->_op_ = this;

    _l_ = in_lhs;
    return in_lhs;
}


#pragma region ast-digraph


/*!
 * \brief node::dot_tree_start
 * \param a_out
 * \param Title
 * \note For now the colours are the halloween theme ;)
 */
void node::dot_tree_start(lus::string& a_out, const lus::string& Title)
{
    a_out << "digraph arithmetic_expressionree {\n";
    a_out << "ratio=compress; ranksep=.55; size = \"6.5,6.5\"; bgcolor=\"#606060\"; \n";
    //a_out << "    node [fontname=\"Source Code Pro\", fontsize=12];\n";
    a_out << "    node [fontname=\"JetBrainsMono NF\", fontsize=18, fontcolor=\"#ff500f\"];\n";
    a_out << "    label = < <u> arithmetic expresion ast : </u> <br/> <br/>" << (std::string)Title << ">; fontsize = 16; fontcolor=\"#00d787\"\n"; // #0FAEFF
}

void node::dot_node(node* _a_, lus::string& a_out)
{
    //static int nullcount = 0;
    if (!_a_) return;
    if ((!_a_->_l_) && (!_a_->_r_)) return;

    if (_a_->_l_) {
        a_out << "    nodeNode" << _a_ << " -> nodeNode" << _a_->_l_ << " [dir = none, Color=\"#A07060\", penwidth=5];\n";
        node::dot_node(_a_->_l_, a_out);
    }

    if (_a_->_r_) {
        a_out << "    nodeNode" << _a_ << " -> nodeNode" << _a_->_r_ << " [dir = none, Color=\"#A07060\", penwidth=5];\n";
        node::dot_node(_a_->_r_, a_out);
    }

}

void node::dot_null_node(node*, int, lus::string&)
{

}

void node::dot_tree(node* a_root, lus::string& a_out)
{
    a_root->dot_attr(a_out);
    node::dot_node(a_root, a_out);
}

void node::dot_tree_close(lus::string& a_out)
{
    a_out << "}\n";
}

void node::dot_attr(lus::string& a_out)
{
    lus::string attr;
    attr << _token_->text();
    lus::string Shape;
    if (_token_->prim & lex::type::Text)
        Shape << "none";
    else
        if (_token_->prim & lex::type::Assign)
            Shape << "none";
        else
            Shape << "none";

    a_out << "    nodeNode" << this << " [shape=\\{s}, label=\"\\{s}\"]\n";
    a_out << Shape() << attr();

    if (_l_)
        _l_->dot_attr(a_out);
    if (_r_)
        _r_->dot_attr(a_out);
}

std::string node::trace_connect_binary_operands(node* x)
{
    // assume this binary operator already has its lhs rhs operands !!
    //lus::string str;
    auto lw = x->_l_->attribute().length();
    auto rw = x->_r_->attribute().length();
    auto ow = x->attribute().length();
    auto w = lw + rw + 3; // total width
    w -= lw % 2 == 0;


    auto m_lhs = lw - (lw > 1 ? 1 : 0);

    ui::cxy oper_xy = ui::cxy(static_cast<int>(m_lhs) + 1, 0);
    oper_xy.x -= ow % 2 == 0 ? 1 : 0;

    ui::string2d area;
    area.set_geometry(static_cast<int>(w), 3); // pour l'instant c'est hardcodé.
    area.gotoxy(oper_xy.x, 0);
    area << x->attribute();
    area << ui::cxy{ static_cast<int>(m_lhs),1 } << "/ \\";

    area.gotoxy(0, 2);
    area << x->_l_->attribute();

    area.gotoxy(static_cast<int>(m_lhs) + 2 + (rw <= 1 ? 1 : 0), 2);
    area << x->_r_->attribute();
    std::string txt = area;
    return txt;
}


std::string node::trace_connect_postfix_operands(node* x)
{
    // assume this binary operator already has its lhs rhs operands !!
    //lus::string str;
    auto lw = x->_l_->attribute().length();
    //auto rw = x->rhs->attribute().length();
    auto ow = x->attribute().length();
    auto w = lw + 3; // total width
    w -= lw % 2 == 0;


    auto m_lhs = lw - (lw > 1 ? 1 : 0);

    ui::cxy oper_xy = ui::cxy(static_cast<int>(m_lhs) + 1, 0);
    oper_xy.x -= ow % 2 == 0 ? 1 : 0;

    ui::string2d area;
    area.set_geometry(static_cast<int>(w), 3); // pour l'instant c'est hardcodé.
    area.gotoxy(oper_xy.x, 0);
    area << x->attribute();
    area << ui::cxy{ static_cast<int>(m_lhs),1 } << "/ \\";

    area.gotoxy(0, 2);
    area << x->_l_->attribute();

    //area.GotoXY(static_cast<int>(m_lhs) + 2;
    //area << x->rhs->attribute();
    return area;
}
#pragma endregion ast-digraph





} // est
