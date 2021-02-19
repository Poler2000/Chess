#ifndef CHESS_CHESSFRAME_H
#define CHESS_CHESSFRAME_H

#include <wx/wxprec.h>
#include <string>
#include <array>
#include "ChessField.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace chessGUI {
    class ChessFrame : public wxFrame {
    public:
        ChessFrame();
        void resetFigures();
        void placeFigure(const std::string& type, int colourId, int x, int y);
    private:
        wxDECLARE_EVENT_TABLE();
        constexpr static char s_defaultTitle[] = "Hello Chess!";
        constexpr static unsigned int s_defWidth = 960;
        constexpr static unsigned int s_defHeight = 720;
        constexpr static int s_defXPos = 10;
        constexpr static int s_defYPos = 10;
        std::array<ChessField, 64> fields;
    };
}

#endif //CHESS_CHESSFRAME_H
