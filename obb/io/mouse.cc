#include <lus/io/mouse.h>
#include <bitset>

namespace lus::io
{




////////////////////////////////////////////////////////////////////////
/// \brief mouse::operator &
/// \param mev
/// \return
/// \note This method is called once the latest mouse data is assigned to this instance so we can evaluate the mouse events according to the comparison against mev
mouse& mouse::operator &(const mouse &mev)
{
    if(std::bitset<2>(mev.button.left) != std::bitset<2>(button.left)){
        // event on left button:
        button.left = mev.button.left == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }
    if(std::bitset<2>(mev.button.right) != std::bitset<2>(button.right)){
        // event on right button:
        button.right = mev.button.right == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }
    if(std::bitset<2>(mev.button.mid) != std::bitset<2>(button.mid)){
        // event on middle button:
        button.mid = mev.button.mid == 1 ? mouse::BUTTON_PRESSED : mouse::BUTTON_RELEASE;
    }

    dxy = pos - mev.pos;
    // todo : Where do I put mouse move event ??
    return *this;
}



} // namespace lus::io

