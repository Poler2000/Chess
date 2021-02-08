#include "chessGUI/ChessFrame.h"

namespace chessGUI {

    wxBEGIN_EVENT_TABLE(ChessFrame, wxFrame)

    wxEND_EVENT_TABLE()

    ChessFrame::ChessFrame()
        : wxFrame(nullptr, wxID_ANY, s_defaultTitle,wxPoint(s_defXPos, s_defYPos), wxSize(s_defWidth, s_defHeight)) {
    }
}

