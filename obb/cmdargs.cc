/******************************************************************************************
*   Copyright (C) ...,2024,... by luxe Lussier                                          *
 *   luxe.lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (luxe Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than luxe Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (luxe Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/



#include <lus/cmdargs.h>
#include <lus/string.h>

namespace lus::cmd
{


cmd_switch::iterator line::query(std::string_view SwitchData)
{
    auto It = arguments.begin();
    for (; It != arguments.end(); It++)
    {
        if ((SwitchData == (*It)->switch_text ) || (SwitchData == (*It)->switch_char))
            return It;
    }
    return arguments.end();
}

line::~line()
{
    arguments.clear(); // doh ...
    //rem::info() << rem::fn::func << "arguments switches infos are cleared.";
}


/*!
 * @brief input operator
 * @param Arg
 * @return Pointer to cmd_switch instance.
 * @author &copy;2023/2024, oldlonecoder/luxe.lussier@oldlonecoder.club
 *
 * @note Because of the action<>, We must instantiate a unique non-copiable cmd_switch using <i>new</i> to ensure
 * that there will be NO move/copy of the instances. We may instantiate directly into the arguments using emplace_back tho. -
 * to be considered...
 */
cmd_switch &line::operator<<(const cmd_switch &Arg)
{
    arguments.push_back(std::make_shared<cmd_switch>());
    cmd_switch::shared Sw = arguments.back();
    Sw->name = Arg.name;
    Sw->switch_char = Arg.switch_char;
    Sw->switch_text = Arg.switch_text;
    Sw->descriptions = Arg.descriptions;
    Sw->required = Arg.required;

    return *Sw;
}




rem::cc line::input(const std::vector<std::string_view>& StrArray)
{
    auto a = arguments.end();

    if(StrArray.empty())
        return rem::cc::empty;

    for(auto sv : StrArray)
    {
        auto next = query(sv);

        //rem::debug() << color::cyan << "line::input" << color::white << '(' << color::yellow << sv << color::white << ") :";

        if(next == arguments.end())
        {
            // It is not a switch - so must be an argument data for the CurArg/NextArg...
            if((a != arguments.end()) &&
                ((*a)->required > (*a)->count) && ((*a)->required > 0))
            {
                (*a)->arguments.emplace_back(sv);
                ++(*a)->count;
                (*a)->enabled = true;
                //rem::debug() << color::yellow << (*a)->name << color::reset << " arg:" << (*a)->count << " '" << sv << '\'';
            }
            else
            {
                // ... or non-switch arg
                defaults.arguments.emplace_back(sv);
                ++defaults.count;
                defaults.enabled = true;
                //rem::debug() << color::yellow << defaults.name << color::reset << " arg:" << defaults.count << " '" << sv << '\'';
            }
        }
        else
        {
            if ((a != arguments.end()) && ((*a)->count < (*a)->required))
            {
                //rem::error() << " argument " << color::yellow << (*a)->name << color::reset << " is missing " << color::red4 << (*a)->required - (*a)->count << color::reset << " arguments / " << color::lime << (*a)->required;
                return rem::cc::failed;
            }
            a = next;
            (*a)->enabled = true;
        }
    }
    return rem::cc::ok;
}


/*!
 * @brief 'runs' the switches hook(s)
 * @return The return action enum value from the last called switch handler.
 */
rem::action  line::process()
{
    auto r = rem::action::end;
    if (!arguments.empty())
    {
        for (const auto& arg : arguments)
        {
            if (arg->enabled)
            {
                if (arg->required > arg->count)
                {
                    arg->enabled = false;
                    // throw rem::except() << " cmd_switch '" << color::yellow << arg->name
                    //     << color::reset << " is missing "
                    //     << color::red4 << arg->required - arg->count
                    //     << color::reset << " arguments: requires "
                    //     << color::lime << arg->required;

                    // // throw did not work? :
                    // rem::except() << " if this is shown, it means exceptions are deactivated. i suggest to enable it... ";
                    // rem::write() << usage();
                    return rem::action::leave;

                }
                if (arg->notify_callback(*arg) != rem::action::cont)
                    return rem::action::leave;
            }
        }
    }
    if(!defaults.arguments.empty())
    {
        if(defaults.enabled)
        {
             r = defaults.notify_callback(defaults);
             if (r != rem::action::cont)
                 return rem::action::leave;
        }
    }
    return rem::action::cont;
}

cmd_switch &line::operator[](const std::string &ArgName)
{
    for(auto Arg :arguments)
    {
        if(Arg->name == ArgName) return *Arg;
    }
    return defaults;
}

std::string line::usage()
{
    lus::string Str;
    Str << "usage:\n";
    lus::string Unused, Used, Used0;

    Unused << color::red1 << glyph::unauth;
    Used   << color::lightgreen2 << glyph::ok;

    Str << "------------------------------------------------------------------------------\n";
    for (auto Arg : arguments)
    {
        Str << std::format("{:>2s} | {:>20s} | {:>45s}",
                Arg->switch_char,
                Arg->switch_text ,
                Arg->descriptions ,
                (Arg->enabled ? Used() : Unused())
            );



        Str << color::reset << "\n------------------------------------------------------------------------------\n";
    }
    return Str();
}


cmd_switch &line::add_cmd(const std::string &cId)
{
    arguments.push_back(std::make_shared<cmd_switch>());
    cmd_switch::shared Sw = arguments.back();
    Sw->name = cId;
    return *Sw;
}


cmd_switch::~cmd_switch()
{
    arguments.clear();
    notify_callback.disconnect_all();
}

cmd_switch &cmd_switch::set_descriptions(const std::string &Txt)
{
    descriptions = Txt;
    return *this;
}

cmd_switch &cmd_switch::set_char(const std::string &Txt)
{
    switch_char = Txt;
    return *this;
}

cmd_switch &cmd_switch::set_long_switch(const std::string &Txt)
{
    switch_text = Txt;
    return *this;
}

cmd_switch &cmd_switch::set_required(int N)
{
    required = N;
    return *this;
}

}
