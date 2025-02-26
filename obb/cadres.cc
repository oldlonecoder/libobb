//
// Created by oldlonecoder on 24-04-02.
//

#include <lus/cadres.h>
#include <stack>
#include <string_view>



namespace lus
{


std::stack<cadre::frame_matrix> cadre::s_fm{};


// From [https://github.com/ArthurSonzogni/FTXUI/blob/main/src/ftxui/screen/string.cpp]
// Adapted for this project.
std::map<std::string_view, cadre::frame_matrix> cadre::s_matrix_data = {
    {"─", {1, 0, 1, 0, 0}},
    {"━", {2, 0, 2, 0, 0}},
    {"╍", {2, 0, 2, 0, 1}},

    {"│", {0, 1, 0, 1, 0}},
    {"┃", {0, 2, 0, 2, 0}},
    {"╏", {0, 2, 0, 2, 1}},

    {"┌", {0, 0, 1, 1, 0}},
    {"┍", {0, 0, 2, 1, 0}},
    {"┎", {0, 0, 1, 2, 0}},
    {"┏", {0, 0, 2, 2, 0}},

    {"┐", {1, 0, 0, 1, 0}},
    {"┑", {2, 0, 0, 1, 0}},
    {"┒", {1, 0, 0, 2, 0}},
    {"┓", {2, 0, 0, 2, 0}},

    {"└", {0, 1, 1, 0, 0}},
    {"┕", {0, 1, 2, 0, 0}},
    {"┖", {0, 2, 1, 0, 0}},
    {"┗", {0, 2, 2, 0, 0}},

    {"┘", {1, 1, 0, 0, 0}},
    {"┙", {2, 1, 0, 0, 0}},
    {"┚", {1, 2, 0, 0, 0}},
    {"┛", {2, 2, 0, 0, 0}},

    {"├", {0, 1, 1, 1, 0}},
    {"┝", {0, 1, 2, 1, 0}},
    {"┞", {0, 2, 1, 1, 0}},
    {"┟", {0, 1, 1, 2, 0}},
    {"┠", {0, 2, 1, 2, 0}},
    {"┡", {0, 2, 2, 1, 0}},
    {"┢", {0, 1, 2, 2, 0}},
    {"┣", {0, 2, 2, 2, 0}},

    {"┤", {1, 1, 0, 1, 0}},
    {"┥", {2, 1, 0, 1, 0}},
    {"┦", {1, 2, 0, 1, 0}},
    {"┧", {1, 1, 0, 2, 0}},
    {"┨", {1, 2, 0, 2, 0}},
    {"┩", {2, 2, 0, 1, 0}},
    {"┪", {2, 1, 0, 2, 0}},
    {"┫", {2, 2, 0, 2, 0}},

    {"┬", {1, 0, 1, 1, 0}},
    {"┭", {2, 0, 1, 1, 0}},
    {"┮", {1, 0, 2, 1, 0}},
    {"┯", {2, 0, 2, 1, 0}},
    {"┰", {1, 0, 1, 2, 0}},
    {"┱", {2, 0, 1, 2, 0}},
    {"┲", {1, 0, 2, 2, 0}},
    {"┳", {2, 0, 2, 2, 0}},

    {"┴", {1, 1, 1, 0, 0}},
    {"┵", {2, 1, 1, 0, 0}},
    {"┶", {1, 1, 2, 0, 0}},
    {"┷", {2, 1, 2, 0, 0}},
    {"┸", {1, 2, 1, 0, 0}},
    {"┹", {2, 2, 1, 0, 0}},
    {"┺", {1, 2, 2, 0, 0}},
    {"┻", {2, 2, 2, 0, 0}},

    {"┼", {1, 1, 1, 1, 0}},
    {"┽", {2, 1, 1, 1, 0}},
    {"┾", {1, 1, 2, 1, 0}},
    {"┿", {2, 1, 2, 1, 0}},
    {"╀", {1, 2, 1, 1, 0}},
    {"╁", {1, 1, 1, 2, 0}},
    {"╂", {1, 2, 1, 2, 0}},
    {"╃", {2, 2, 1, 1, 0}},
    {"╄", {1, 2, 2, 1, 0}},
    {"╅", {2, 1, 1, 2, 0}},
    {"╆", {1, 1, 2, 2, 0}},
    {"╇", {2, 2, 2, 1, 0}},
    {"╈", {2, 1, 2, 2, 0}},
    {"╉", {2, 2, 1, 2, 0}},
    {"╊", {1, 2, 2, 2, 0}},
    {"╋", {2, 2, 2, 2, 0}},

    {"═", {3, 0, 3, 0, 0}},
    {"║", {0, 3, 0, 3, 0}},

    {"╒", {0, 0, 3, 1, 0}},
    {"╓", {0, 0, 1, 3, 0}},
    {"╔", {0, 0, 3, 3, 0}},

    {"╕", {3, 0, 0, 1, 0}},
    {"╖", {1, 0, 0, 3, 0}},
    {"╗", {3, 0, 0, 3, 0}},

    {"╘", {0, 1, 3, 0, 0}},
    {"╙", {0, 3, 1, 0, 0}},
    {"╚", {0, 3, 3, 0, 0}},

    {"╛", {3, 1, 0, 0, 0}},
    {"╜", {1, 3, 0, 0, 0}},
    {"╝", {3, 3, 0, 0, 0}},

    {"╞", {0, 1, 3, 1, 0}},
    {"╟", {0, 3, 1, 3, 0}},
    {"╠", {0, 3, 3, 3, 0}},

    {"╡", {3, 1, 0, 1, 0}},
    {"╢", {1, 3, 0, 3, 0}},
    {"╣", {3, 3, 0, 3, 0}},

    {"╤", {3, 0, 3, 1, 0}},
    {"╥", {1, 0, 1, 3, 0}},
    {"╦", {3, 0, 3, 3, 0}},

    {"╧", {3, 1, 3, 0, 0}},
    {"╨", {1, 3, 1, 0, 0}},
    {"╩", {3, 3, 3, 0, 0}},

    {"╪", {3, 1, 3, 1, 0}},
    {"╫", {1, 3, 1, 3, 0}},
    {"╬", {3, 3, 3, 3, 0}},

    {"╭", {0, 0, 1, 1, 1}},
    {"╮", {1, 0, 0, 1, 1}},
    {"╯", {1, 1, 0, 0, 1}},
    {"╰", {0, 1, 1, 0, 1}},

    {"╴", {1, 0, 0, 0, 0}},
    {"╵", {0, 1, 0, 0, 0}},
    {"╶", {0, 0, 1, 0, 0}},
    {"╷", {0, 0, 0, 1, 0}},

    {"╸", {2, 0, 0, 0, 0}},
    {"╹", {0, 2, 0, 0, 0}},
    {"╺", {0, 0, 2, 0, 0}},
    {"╻", {0, 0, 0, 2, 0}},

    {"╼", {1, 0, 2, 0, 0}},
    {"╽", {0, 1, 0, 2, 0}},
    {"╾", {2, 0, 1, 0, 0}},
    {"╿", {0, 2, 0, 1, 0}}
};


void cadre::push(cadre::frame_matrix FrameModel)
{
    // if(cadre::s_fm.empty())
    //     cadre::s_fm.push({2,2,2,2,0});
    cadre::s_fm.push(FrameModel);
}



void cadre::pop()
{
    if(!cadre::s_fm.empty())
        cadre::s_fm.pop();
}


cadre &cadre::operator=(cadre::frame_matrix ModelArg)
{
    frame = ModelArg;
    return *this;
}


/*!
 * @brief Mandatory operator less than for reverse map.
 * @param RHS
 * @return true or false for the obvious reasons.
 * @note  : Source : https://github.com/ArthurSonzogni/FTXUI/blob/main/src/ftxui/screen/string.cpp
 */
bool cadre::frame_matrix::operator<(cadre::frame_matrix RHS) const
{
    if (Left < RHS.Left)   { return  true;  }
    if (Left > RHS.Left)   { return  false; }
    if (Top <  RHS.Top)    { return  true;  }
    if (Top >  RHS.Top)    { return  false; }
    if (Right < RHS.Right) { return  true;  }
    if (Right > RHS.Right) { return  false; }
    if (Down < RHS.Down)   { return  true;  }
    if (Down > RHS.Down)   { return  false; }
    if (Round < RHS.Round) { return  true;  }
    if (Round > RHS.Round) { return  false; }
    return false;
}

/*!
 * @brief Assign the Frame data using the provided Frame model;
 * @param FrameModel
 * @return ref to self.
 * @author  oldlonecoder (oldlonecoder@oldlonecoder.club)
 */
cadre::frame_data &cadre::frame_data::operator=(cadre::frame_matrix const FrameModel)
{
    std::map<cadre::frame_matrix, std::string_view> _;
    for(const auto& X: cadre::s_matrix_data)
    {
        _[X.second] = X.first;
    }
    CDT = _[{FrameModel.Left, FrameModel.Top, FrameModel.Right, 0              , 0}].data();
    CTD = _[{FrameModel.Left, 0             , FrameModel.Right, FrameModel.Down, 0}].data();
    CLR = _[{0              , FrameModel.Top, FrameModel.Right, FrameModel.Down, 0}].data();
    CRL = _[{FrameModel.Left, FrameModel.Top, 0               , FrameModel.Down, 0}].data();
    CVH = _[{FrameModel.Left, FrameModel.Top, FrameModel.Right, FrameModel.Down, 0}].data();
    VL  = _[{0              , FrameModel.Top, 0               , FrameModel.Down, 0}].data();
    HL  = _[{FrameModel.Left, 0             , FrameModel.Right, 0              , 0}].data();
    BR  = _[{FrameModel.Left, FrameModel.Top, 0               , 0              , FrameModel.Round}].data();
    BL  = _[{0, FrameModel.Top, FrameModel.Right          , 0              , FrameModel.Round}].data();
    TR  = _[{FrameModel.Left, 0             , 0               , FrameModel.Down, FrameModel.Round}].data();
    TL  = _[{0              , 0             , FrameModel.Right, FrameModel.Down, FrameModel.Round}].data();
    return *this;
}


cadre::cadre()
{
    if(cadre::s_fm.empty())
        cadre::push(_model_);

    _model_ = cadre::s_fm.top();
    frame = _model_;
}


}
