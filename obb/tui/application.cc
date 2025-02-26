#include <lus/ui/application.h>
#include <csignal>
//#include <lus/ui/console.h>
#include <lus/io/kbhit.h>


namespace lus::ui
{


application* application::_app{nullptr};
void application::sig_interrupted(int)
{
    journal::interrupted() << journal::endl;
    console::end();
    //book::purge(nullptr);
    application::app().terminate(rem::type::interrupted);
    exit(0);
}

void application::sig_aborted(int)
{
    journal::aborted() << journal::endl;;
    console::end();
    //book::purge(nullptr);
    application::app().terminate(rem::type::aborted);
    exit(0);
}

void application::sig_crash(int)
{
    journal::segfault() << journal::endl;;
    console::end();
    application::app().terminate(rem::type::segfault);
    exit(0);
}





lus::ui::application::application(const std::string &app_id, string::view_list _args_): _id(app_id)
{
    if(!journal::is_init())
        journal::init(app_id);

    if(application::_app)
    {
        journal::fatal() << rem::cc::exist << " -> lus::ui::application instance already exists. " << journal::eol;
        ::abort();
    }
    _app = this;
    journal::info() << " lus::ui::application instance created and " << rem::cc::ready << journal::eol;
}



application::~application(){}


rem::cc application::install_signals()
{
    if(!application::_app)
        journal::exception() [ journal::fatal() << " application instance must be created prior to install signals." << journal::eol];

    std::signal(SIGSEGV, &application::sig_crash);
    std::signal(SIGABRT, &application::sig_aborted);
    std::signal(SIGINT, &application::sig_interrupted);
    //std::signal(SIGWINCH, &application::sig_winch);
    journal::info() << rem::cc::done << journal::endl;
    return rem::cc::done;
}


rem::cc application::setup()
{
    setup_journal();
    console::begin(/*console::SAVE_SCREEN*/);
    console::init_stdinput();
    return rem::cc::ready;
}

rem::cc application::setup_ui()
{
    return rem::cc::notimplemented;
}

rem::cc application::run()
{
    // auto r = setup_ui();

    return rem::cc::notimplemented;
}

rem::cc application::terminate(rem::type reason_type)
{
    journal::status() << reason_type << journal::eol;
    _listener.terminate();
    console::end();
    if(journal::is_init())
        journal::end();

    return rem::cc::terminate;
}

application& application::app()
{
    if(!application::_app)
    {
        journal::fatal() << rem::cc::notexist << " -> lus::ui::application instance was not created. " << journal::eol;
        ::abort();
    }

    return *application::_app;
}


rem::cc application::setup_journal()
{
    journal::init("lus.app");
    journal::status() << rem::cc::ready << journal::eol;
    //...
    return rem::cc::ready;
}

rem::action application::poll_event()
{
    do{
        auto [r, in] = console::poll_in();

    }while(1);
    return rem::action::end;
}



}

