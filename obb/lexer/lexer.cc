//
// Created by oldlonecoder on 24-03-08.
//

#include <lus/lexer/lexer.h>
#include <lus/journal.h>

namespace lus
{


rem::cc lexer::exec()
{
    journal::debug() << " Verify config data:" << journal::eol;
    if(!m_config.production)
    {
        journal::error() << " config data is empty!" << journal::endl;
        return rem::cc::null_ptr;
    }

    //journal::debug() << " Now Building the Tokens Reference Table:" << journal::eol;
    m_config.production->set_reference_table();
    if(m_config.text.empty() || m_config.production->reference_table().empty())
    {
        //journal::error() << " config data is empty!" << journal::eol;
        return rem::cc::empty;
    }

    //journal::debug() << " Here is the ref_table Table Dump:"  << journal::eol;
    m_config.production->dump_reference_table();

    //return rem::cc::Ok;

    scanner = m_config.text;
    scanner.skip_ws();

    return loop();
}


/*!
 * @brief Virtual loop
 *
 * @return rem::cc::Code...
 */
rem::cc lexer::loop()
{
    journal::debug() << "Before entering the loop: " << journal::eol;
    journal::write() << " scanner position set at (col:" << scanner()-scanner.begin() << "):{" << scanner.mark() << rem::fn::endl << "}" << journal::endl;
    journal::test() << " now entering in the loop:" << journal::eol;
    //return rem::cc::Ok;
    auto Cursor = scanner(); // Save current position.
    while(!scanner.eof() && (state != rem::cc::eof))
    {
        //journal::debug() << " lexer::loop [Next Token]: " << scanner.mark() << journal::eol;
        lex_token Token{};

        if(!!tokenize_numeric(Token))
        {
            journal::debug() << "token is numeric expr : " << rem::fn::endl << Token.details() << rem::fn::endl << Token.mark(m_config.text.data()) << journal::endl;
            if(scanner.eof() || (state == rem::cc::eof))
                return rem::cc::accepted;
        }
        else
            if(!!tokenize(m_config.production->scan(scanner())))
            {
                journal::debug() << " token matches table: " << scanner.mark() << journal::eol;
            }

        if(Cursor == scanner())
        {
            journal::error() << " loop: no scanning (unhandled yet or bug ;) )" << rem::fn::endl << scanner.mark() << journal::endl;
            return rem::cc::rejected;
        }

        Cursor = scanner();
    }

    return rem::cc::accepted;

}




rem::cc lexer::tokenize(lex_token Token)
{
    journal::debug() <<  scanner.mark(); //not scanned yet that's why it doen's have line and col numbers ...yet
    journal::debug() << Token.type_name() << ',' << color::lightsalmon4 <<  Token.token_location.begin <<journal::eol;

    static std::map<lex::type::T, rem::cc (lexer::*)(lex_token&)> ScanFn = {
        {lex::type::Binary           , &lexer::tokenize_binary_operator},
        {lex::type::Null             , &lexer::tokenize_default},
        {lex::type::Unary            , &lexer::tokenize_unary_operator},
        {lex::type::Punc             , &lexer::tokenize_punctuation},
        {lex::type::Keyword          , &lexer::tokenize_keyword},
        {lex::type::Text             , &lexer::tokenize_string},
        {lex::type::Prefix           , &lexer::tokenize_prefix},
        {lex::type::Postfix          , &lexer::tokenize_postfix},
        {lex::type::LineComment      , &lexer::tokenize_cpp_comment},
        {lex::type::BlocComment      , &lexer::tokenize_comment_bloc}
    };

    rem::cc r{rem::cc::rejected};
    for(auto [T, Fn] : ScanFn)
    {
        if(T & Token.sem)
           return (this->*Fn)(Token);
    }
    return r;
}




rem::cc lexer::tokenize_binary_operator(lex_token &newtoken)
{
    journal::debug() << newtoken.details() << scanner.mark() << journal::eol;
    (void)tokenize_sign_prefix(newtoken);
    newtoken.token_location = scanner.sync();
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken); // s'occupera de mettre à jour le token et d'avancer le tscanner. ;)

    return rem::cc::accepted;
}

rem::cc lexer::tokenize_default(lex_token &newtoken)
{
    journal::debug() << " entering with:" << (newtoken ? newtoken.details() : scanner.mark()) << journal::eol;
    return tokenize_identifier(newtoken);
    //}
   // return rem::cc::Accepted;
}


rem::cc lexer::tokenize_unary_operator(lex_token &newtoken)
{
    newtoken.token_location = scanner.sync();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    journal::debug() << newtoken.details() << journal::eol;
    push_token(newtoken);
    journal::debug() << "pushed: " << newtoken.details() << journal::eol;
    return rem::cc::accepted;
}

rem::cc lexer::tokenize_punctuation(lex_token &newtoken)
{
    journal::debug() << rem::fn::func << " sync'ing the scanner:" << journal::eol;
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    journal::debug() << "pushing new [punctuation] token" << journal::eol;
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken);
    journal::debug() << "pushed: " << rem::fn::func << newtoken.details();
    return rem::cc::accepted;
}

rem::cc lexer::tokenize_keyword(lex_token &newtoken)
{
    journal::debug() << " sync'ing the scanner:";
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    journal::debug() << "pushing new [keyword] token";
    push_token(newtoken);
    journal::debug() << "pushed: " << newtoken.details();
    return rem::cc::accepted;
}


rem::cc lexer::tokenize_string(lex_token &newtoken)
{
    journal::debug() << " sync'ing the scanner:" << journal::eol;
    newtoken.token_location = scanner.sync();
    journal::write() << " scanner: " << scanner.mark() << journal::eol;
    journal::write() << rem::cc::notimplemented << journal::eol;
    auto r = scanner.scan_literal_string();
    journal::debug() << "scanner.scan_literal_string() returned:" << r.first << journal::endl;
    if(!r.first)
        return r.first;

    journal::debug() << " Filling new string token:" << journal::endl;
    newtoken.token_location = scanner.sync();
    newtoken.token_location.length = r.second.length();
    newtoken.token_location.begin = r.second.begin();
    newtoken.token_location.end = r.second.end();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken);
    journal::debug() << "pushed: " << newtoken.details();
    return rem::cc::accepted;
}


rem::cc lexer::tokenize_identifier(lex_token &newtoken)
{
    journal::debug() << scanner.mark() << journal::endl; //scanner.Mark();
    auto i = scanner.scan_identifier();
    journal::debug() << "scanner.scan_identifier() returned:" << i.first << journal::endl;
    if(!i.first)
        return i.first;


    journal::debug() << " Filling new identifier token:" << journal::endl;
    newtoken.token_location = scanner.sync();
    newtoken.token_location.length = i.second.length();
    newtoken.token_location.begin = i.second.begin();
    newtoken.token_location.end = i.second.end() - 1;
    newtoken.name    = lex::lexem::Identifier;
    newtoken.prim    =lex::type::Id;
    newtoken.sem     =lex::type::Id|lex::type::Leaf;
    newtoken.flags = { .V = 1 };
    journal::debug() << "Pushing New [Identifier] Token" << journal::endl;
    (*m_config.production) << newtoken;
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    scanner.skip_ws();
    journal::debug() << "Pushed: " << newtoken.details() << journal::endl;

    return rem::cc::accepted;
}

rem::cc lexer::tokenize_sign_prefix(lex_token &newtoken)
{
    journal::debug() << rem::fn::func << ":";
    if ((newtoken.m != lex::mnemonic::Sub) && (newtoken.m != lex::mnemonic::Add))
    {
        journal::write() << " rejected (not subtract or addition operator).";
        return rem::cc::rejected;
    }

    if(!m_config.production->empty())
    {
        auto &token = m_config.production->production_table().back();
        journal::write() << "prev: " << token.details(true);
        if((!token.has_type(lex::type::Binary |lex::type::Punc)) || (token.m == lex::mnemonic::ClosePar))
        {
            journal::write() << " rejected: previous token is not an operator or a expression-terminating punctuation token";
            return rem::cc::rejected;
        }
    }

    journal::write() << " conditions met for unary prefix sign operator:";
    newtoken.prim =lex::type::Sign;
    newtoken.sem = (newtoken.sem & ~(lex::type::Postfix|lex::type::Binary)) | lex::type::Prefix |lex::type::Unary | lex::type::Operator| lex::type::Sign;
    newtoken.m = lex::mnemonic::Negative;
    newtoken.token_location.length = 1;
    newtoken.token_location.end = newtoken.token_location.begin + 1;
    return rem::cc::accepted;
}



/*!
 * @brief tokenize prefix operator after verifying that the prefix-operator is well formed and does not break the arithmetic syntax rules
 * @param newtoken
 *
 * @note a * *B;
 * @return rem::cc::Code
 */
rem::cc lexer::tokenize_prefix(lex_token &newtoken)
{
    if ((newtoken.m == lex::mnemonic::Decr) || (newtoken.m == lex::mnemonic::Incr) || (newtoken.m == lex::mnemonic::BinaryNot))
    {
        if(production().empty())
        {
            push_token(newtoken);
            return rem::cc::accepted;
        }
        if((production().back().flags.V) && (!production().back().has_type(lex::type::Operator)))
        {
            newtoken.prim   = lex::type::Postfix;
            newtoken.sem    &= ~lex::type::Prefix |lex::type::Postfix;
            if(newtoken.m   == lex::mnemonic::BinaryNot)
                newtoken.m  = lex::mnemonic::Factorial;
        }
        if(!production().back().flags.V)
            throw journal::exception()[ journal::syntax() << newtoken.details() << ": illegal; "];
    }
    push_token(newtoken);

    return rem::cc::accepted;
}




rem::cc lexer::tokenize_postfix(lex_token &newtoken)
{

    if((production().empty()) || (!production().back().flags.V))
        throw journal::exception()[ journal::syntax() << newtoken.details() << ": illegal;"];

    push_token(newtoken);

    return rem::cc::ok;
}

rem::cc lexer::tokenize_cpp_comment(lex_token &newtoken)
{
    return rem::cc::ok;
}

rem::cc lexer::tokenize_comment_bloc(lex_token &newtoken)
{
    return rem::cc::ok;
}


rem::cc lexer::tokenize_numeric(lex_token& newtoken)
{
    auto R = scanner.scan_number();
    if(!!R.first)
    {
        newtoken.num_data = lus::sscan::numeric::details{R.second};
        newtoken.token_location = scanner.sync();
        newtoken.token_location.length = newtoken.num_data.seq.length();
        newtoken.token_location.begin  = newtoken.num_data.seq.begin();
        newtoken.token_location.end    = newtoken.num_data.seq.end();
        newtoken.prim       =lex::type::Number;
        newtoken.name       = lex::lexem::Numeric;
        state = scanner.step(static_cast<int32_t>(newtoken.num_data.seq.length()));
        newtoken.numeric_tr();
        (*m_config.production) << newtoken;
        state = scanner.skip_ws() ? rem::cc::eof : rem::cc::ok;

        return rem::cc::accepted;
    }
    return rem::cc::rejected;
}


/*!
 * @brief
 * @param Token
 *
 * @todo Assign location data here.
 */
void lexer::push_token(lex_token &newtoken)
{
    journal::debug() << " Pushing new token : " << rem::fn::endl  << newtoken.details() << journal::endl;
    journal::write() << newtoken.mark(m_config.text.data()) << journal::endl;

    (*m_config.production) << newtoken;

    //scanner.Sync(newtoken.token_location.length);
    journal::debug() << "SkipWS: ";
    scanner.skip_ws();
}

lex_token::list& lexer::production()
{
    return m_config.production->ref_table;
}

void lexer::update_token_location(lex_token &newtoken)
{

}


} // lex
