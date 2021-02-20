#ifndef CHESS_CHESSFRAME_H
#define CHESS_CHESSFRAME_H

#include <wx/wxprec.h>
#include <string>
#include <memory>
#include <array>
#include "ChessField.h"
#include "app/Launcher.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class Launcher;

namespace chessGUI {

    class ChessFrame : public wxFrame {
    public:
        ChessFrame(std::shared_ptr<Launcher>);
        void resetFigures();
        void placeFigure(int id, const std::string& type, int colourId, int x, int y);
        void onFigureClicked(wxMouseEvent& ev);
    private:
    wxDECLARE_EVENT_TABLE();
        constexpr static char s_defaultTitle[] = "Hello Chess!";
        constexpr static unsigned int s_defWidth = 960;
        constexpr static unsigned int s_defHeight = 720;
        constexpr static int s_defXPos = 10;
        constexpr static int s_defYPos = 10;
        constexpr static uint16_t s_redId = 1;
        constexpr static uint16_t s_blueId = 7;

        std::shared_ptr<Launcher> launcher;
        std::array<ChessField, 64> fields;
    };
}

#endif //CHESS_CHESSFRAME_H
