#include <obb/logbook.h>
#include <obb/io/terminal.h>


namespace obb
{


class test
{
    io::terminal term{nullptr,"tests",{}};
    obb::string::view_list _args{};
public:
    test(const std::string& tname, obb::string::view_list&& vargs);
    ~test(){ _args.clear(); }

    void terminate();
    rem::cc run();

};




rem::cc test::run()
{
    book::init("obb_test");
    term.begin("obb test");
    term.init_stdinput();
    try{
        do{
            auto r = term.poll_in();
            if(!r){
                terminate();
                return rem::cc::terminate;
            }
            for(; term.events().empty(); term.events().pop_front()){
                auto evc = term.events().front();
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
                else if(evc.is<io::mouse>()){
                        book::message() << "mouse event at position: " << evc.data.mev.pos << book::eol;
                }
            }
        }while(1);

    }catch(book::exception& be){
        std::cout << be.what();
        terminate();
        return rem::cc::terminate;
    }
    return rem::cc::ok;
}



test::test(const std::string &tname, string::view_list &&vargs): _args(std::move(vargs)){}


void test::terminate()
{
    term.end();
    book::end();
}

}



auto main(int argc, char** argv, char** env) -> int
{
    std::cout << "Hello, World\n";
    obb::test tests("obb tests", obb::string::string_view_list(argc,argv,1));
    return static_cast<int>(tests.run());
}

