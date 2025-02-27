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
    auto [r, in] = io::console::poll_in();
    if(in.is<io::kbhit>())
    {
        ;
    }
    io::console::end();
    book::end();
    return rem::cc::ok;
}


}



auto main(int argc, char** argv, char** env) -> int
{
    std::cout << "Hello, World\n";
    obb::test();
    return 0;
}
