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


#include <obb/ui/console.h>
#include <obb/cmdargs.h>
#include <obb/io/listener.h>
#include <obb/io/kbhit.h>

namespace obb::ui
{


class LUSTUILIB application
{
    std::string _id{};
    obb::string::view_list _args{};
    static application* _app;
    console             _console{"console"};
    io::listener _listener{"Application Console Input"};
    cmd::line   _cmdl{};
    static void sig_interrupted(int);
    static void sig_aborted(int);
    static void sig_crash(int);
    virtual rem::cc install_signals();
public:
    application()=default;
    application(const std::string& _id, obb::string::view_list _args_);
    virtual ~application();

    virtual rem::cc setup();
    virtual rem::cc setup_ui();
    virtual rem::cc run();
    virtual rem::cc terminate(rem::type reason_type);

    static application& app();


protected:
    rem::action stdin_ready(io::lfd& _fd);
    virtual rem::cc setup_book();
    rem::action poll_event();

};

}

