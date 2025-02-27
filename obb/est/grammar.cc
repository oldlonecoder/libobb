


#include <obb/est/grammar.h>
#include <obb/lexer/tokens_table.h>

#include <obb/logbook.h>
//#include <obb/ui/tuxns.h>


namespace obb::est
{



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



std::map<std::string, grammar::rule*> rules{};


static std::map<char, ui::color::pair> properties_colors
{
    {grammar::OPTIONAL,     {ui::color::cyan3,                ui::color::reset}},
    {grammar::REPEAT,       {ui::color::lime,                 ui::color::reset}},
    {grammar::ONEOF,        {ui::color::red4,                 ui::color::reset}},
    {grammar::EXCLUDE,      {ui::color::lightskyblue4,        ui::color::reset}},
    {grammar::DIRECTIVE,    {ui::color::yellow,               ui::color::reset}},
    {grammar::REJECTED,     {ui::color::violet,               ui::color::reset}}
};

static std::map<grammar::term::type, ui::color::pair> term_colors
{
    {grammar::term::type::rule_type,      {ui::color::lightpink4,       ui::color::reset}},
    {grammar::term::type::semantic_type,  {ui::color::lime,             ui::color::reset}},
    {grammar::term::type::mnemonic_type,  {ui::color::lightskyblue4,    ui::color::reset}},

};


static std::map<char, ui::color::pair> punctuation_colors
{
    {':', {ui::color::chartreuse6,   ui::color::reset}},
    {'|', {ui::color::yellow,        ui::color::reset}},
    {'.', {ui::color::lime,          ui::color::reset}},
    {'\'', {ui::color::lime,          ui::color::reset}},
    {'"', {ui::color::lime,          ui::color::reset}}
};



std::string grammar::props::to_string() const
{

    obb::string _str{};

    if(z) _str << properties_colors[OPTIONAL ];
    if(r) _str << properties_colors[REPEAT   ];
    if(l) _str << properties_colors[ONEOF    ];
    if(x) _str << properties_colors[EXCLUDE  ];
    if(e) _str << properties_colors[DIRECTIVE];
    if(s) _str << properties_colors[REJECTED ];
    return _str();
}


std::string grammar::term::to_string(lexer::config_data& _data) const
{
    obb::string str;
    str << _props_.to_string() << term_colors[_type_];
    lex_token tok{};
    switch(_type_)
    {
        case grammar::term::type::mnemonic_type:
        {
            tok = (*_data.production)[_store_._mnemonic_];
            str << tok.text().data(); // String (TEXT)
        }
        break;
        case grammar::term::type::rule_type:
            // Can't happen but we never know: (nullptr)
                if(_store_._rule_)
                    str << _store_._rule_->name;
        break;
        case grammar::term::type::semantic_type:
            str << lexer_component::type_name(_store_._semantic_);
        break;
        default:
            str << "nil";
        break;
    }

    return str();
}


grammar::rule& grammar::rule::new_sequence()
{
    sequences.emplace_back();
    index = sequences.begin();
    return *this;
}


grammar::grammar(const std::string& _name, lexer::config_data _cfg_data) : _config_data_(_cfg_data) { }





rem::cc grammar::build(const std::string& _name)
{
    _config_data_.text = _config_data_.text.empty() ? grammar_text: _config_data_.text;
    if (!_config_data_.production)
    {
        book::fatal() << "grammar::build: no token_table provided!" << book::endl;
        return rem::cc::failed;
    }

    lexer _lexer;
    _lexer.config() = _config_data_;
    if (auto r = _lexer.exec(); !r )
    {
        book::fatal() << " lexer: " << r << book::endl;
        return r;
    }

    book::status() << rem::cc::success <<  " - tokens count:" << ui::color::lime << _config_data_.production->count() << book::endl;

    ///... to be continued
    return rem::cc::notimplemented;
}



}
