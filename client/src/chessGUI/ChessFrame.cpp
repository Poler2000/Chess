#include <vector>
#include "chessGUI/ChessFrame.h"

namespace chessGUI {

    wxBEGIN_EVENT_TABLE(ChessFrame, wxFrame)
    wxEND_EVENT_TABLE()

    ChessFrame::ChessFrame()
        : wxFrame(nullptr, wxID_ANY, s_defaultTitle,wxPoint(s_defXPos, s_defYPos), wxSize(s_defWidth, s_defHeight)) {

        wxSizer* sizer = new wxGridSizer(8, 8, 0, 0);
        std::for_each(fields.begin(), fields.end(), [&, i = 0, p = 0](auto& field) mutable {
            field.Create(this, 10000 + ++i);
            field.SetBackgroundColour((i % 2 == p) ? *wxBLACK : *wxWHITE);
           // field.setImage(wxT("../resources/BlueQueen.png"), wxBITMAP_TYPE_PNG);
            p = (i % 8 == 0) ? -p + 1 : p;
            sizer->Add(&field, 1, wxEXPAND);
        });

        this->SetSizer(sizer);
        sizer->Layout();
    }

    void ChessFrame::resetFigures() {
        std::for_each(fields.begin(), fields.end(), [&](auto& field) {
            field.resetImage();
        });
    }

    void ChessFrame::placeFigure(const int id, const std::string &type, const int colourId, const int x, const int y) {
        std::cout << "id: " << id << " type: " << type << " colour: " << colourId << " x: " << x << " y: " << y << '\n';
        std::string colour = colourId == s_blueId ? "Blue" : "Red";
        std::string path = std::string("../resources/") + colour + type + std::string(".png");
        fields[8 * y + x].setImage(path, wxBITMAP_TYPE_PNG);
    }

}

