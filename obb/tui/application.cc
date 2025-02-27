#include <obb/ui/application.h>
#include <csignal>
//#include <obb/ui/console.h>
#include <obb/io/kbhit.h>


namespace obb::ui
{


application* application::_app{nullptr};
void application::sig_interrupted(int)
{
    book::interrupted() << book::endl;
    console::end();
    //book::purge(nullptr);
    application::app().terminate(rem::type::interrupted);
    exit(0);
}

void application::sig_aborted(int)
{
    book::aborted() << book::endl;;
    console::end();
    //book::purge(nullptr);
    application::app().terminate(rem::type::aborted);
    exit(0);
}

void application::sig_crash(int)
{
    book::segfault() << book::endl;;
    console::end();
    application::app().terminate(rem::type::segfault);
    exit(0);
}





obb::ui::application::application(const std::string &app_id, string::view_list _args_): _id(app_id)
{
    if(!book::is_init())
        book::init(app_id);

    if(application::_app)
    {
        book::fatal() << rem::cc::exist << " -> obb::ui::application instance already exists. " << book::eol;
        ::abort();
    }
    _app = this;
    book::info() << " obb::ui::application instance created and " << rem::cc::ready << book::eol;
}



application::~application(){}


rem::cc application::install_signals()
{
    if(!application::_app)
        book::exception() [ book::fatal() << " application instance must be created prior to install signals." << book::eol];

    std::signal(SIGSEGV, &application::sig_crash);
    std::signal(SIGABRT, &application::sig_aborted);
    std::signal(SIGINT, &application::sig_interrupted);
    //std::signal(SIGWINCH, &application::sig_winch);
    book::info() << rem::cc::done << book::endl;
    return rem::cc::done;
}


rem::cc application::setup()
{
    setup_book();
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
    book::status() << reason_type << book::eol;
    _listener.terminate();
    console::end();
    if(book::is_init())
        book::end();

    return rem::cc::terminate;
}

application& application::app()
{
    if(!application::_app)
    {
        book::fatal() << rem::cc::notexist << " -> obb::ui::application instance was not created. " << book::eol;
        ::abort();
    }

    return *application::_app;
}


rem::cc application::setup_book()
{
    book::init("lus.app");
    book::status() << rem::cc::ready << book::eol;
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

