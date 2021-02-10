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
            field.setImage(wxT("../resources/BlueQueen.png"), wxBITMAP_TYPE_PNG);
            p = (i % 8 == 0) ? -p + 1 : p;
            sizer->Add(&field, 1, wxEXPAND);
        });

        /*wxSizer* butSizer = new wxBoxSizer(wxVERTICAL);

        gameList.Create(this, wxID_ANY);

        wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(&gameList, 1, wxEXPAND | wxLEFT | wxRIGHT);
        std::for_each(buttons.begin(), buttons.end(), [&, i = 0](auto& button) mutable {
            button.Create(this, wxID_ANY, std::string{s_butTitles[i++]});
            butSizer->Add(&button, 1, wxEXPAND);
        });
        sizer->Add(butSizer, 1, wxEXPAND);*/
        this->SetSizer(sizer);
        sizer->Layout();
    }

}

