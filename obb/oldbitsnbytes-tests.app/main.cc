#include <obb/logbook.h>
#include <obb/io/console.h>


namespace obb
{

rem::cc test()
{

    book::init("obb++.test");
    io::console con{"obb++.test"};
    book::message() << "Hello, World" << book::endl;
    io::console::begin();
    io::console::init_stdinput();
cont:
    auto [r, in] = io::console::poll_in();
    if(in.is<io::kbhit>()){
        if(in.data.kev.mnemonic == io::kbhit::ESCAPE){
            book::message() << "ESCAPE KEY hit - Terminating!." << book::eol;
            io::console::end();
            book::end();
            return rem::cc::terminate;
        }
    }
    goto cont;
}


}



auto main(int argc, char** argv, char** env) -> int
{
    std::cout << "Hello, World\n";
    obb::test();
    return 0;
}
