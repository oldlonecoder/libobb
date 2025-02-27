#include <obb/logbook.h>
#include <obb/io/console.h>


namespace obb
{

rem::cc test()
{
    io::console::begin();
    io::console::init_stdinput();
    auto [r, in] = io::console::poll_in();
    if(in.is<io::kbhit>());
    return rem::cc::ok;
}


}



auto main(int argc, char** argv, char** env) -> int
{
    std::cout << "Hello, World\n";
    return 0;
}
