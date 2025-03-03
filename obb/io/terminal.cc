#include <obb/io/terminal.h>

namespace obb::io
{



bool terminal::cursor(cxy xy)
{
    if(!_geometry.goto_xy(xy)) return false;
    std::cout << std::format("\x1b[{:d};{:d}H", xy.y+1,xy.x+1);
    return true;
}












namespace terminals
{
terminal& new_terminal(const std::string& id, terminal* parent_terminal = nullptr)
{

    auto* t = new terminal(parent_terminal,id, {});

}
//...
}

} // namespace obb::io
