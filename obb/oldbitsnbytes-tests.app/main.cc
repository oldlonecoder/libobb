#include <obb/logbook.h>
#include <obb/io/terminal.h>


namespace obb
{



void terminate()
{
    io::console::end();
    book::end();
}

rem::cc test()
{

    book::init("obb++.test");
    io::console con{"obb++.test"};
    book::message() << "Hello, World" << book::endl;
    io::console::begin();
    //io::console::init_stdinput();

    try{
        do{
            auto r = io::console::poll_in();
            if(!!r){
                for(; !io::console::get_current().events().empty();io::console::get_current().events().pop_front()){
                    auto evc = io::console::get_current().events().front();
                    if(evc.is<io::kbhit>()){
                        book::debug() << "kbhit:" << evc.data.kev.name << book::eol;
                        if(evc.data.kev.mnemonic == io::kbhit::ESCAPE){
                            book::message() << "ESCAPE KEY hit - Terminating!." << book::eol;
                            terminate();
                            return rem::cc::terminate;
                        }
                        else{
                            book::message() << "CHARACTER or command: " << evc.data.kev.name << " | " << (char)evc.data.kev.code << book::eol;
                        }
                    }
                    else
                        if(evc.is<io::mouse>()){
                            book::message() << "mouse event at position: " << evc.data.mev.pos << book::eol;
                    }
                }
            }
        }while(1);
    }
    catch(book::exception& e){
        std::cout << e.what() << std::endl;
        terminate();
    }
    return rem::cc::terminate;
}


}



auto main(int argc, char** argv, char** env) -> int
{
    std::cout << "Hello, World\n";
    obb::test();
    return 0;
}
