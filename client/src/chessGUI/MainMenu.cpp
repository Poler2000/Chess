#include "chessGUI/MainMenu.h"

namespace chessGUI {
    wxBEGIN_EVENT_TABLE(MainMenu, wxFrame)
    wxEND_EVENT_TABLE()

    MainMenu::MainMenu()
            : wxFrame(nullptr, wxID_ANY, s_defaultTitle,wxPoint(s_defXPos, s_defYPos), wxSize(s_defWidth, s_defHeight)) {
        wxSizer* butSizer = new wxBoxSizer(wxVERTICAL);

        gameList.Create(this, wxID_ANY);

        wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(&gameList, 1, wxEXPAND | wxLEFT | wxRIGHT);
        std::for_each(buttons.begin(), buttons.end(), [&, i = 0](auto& button) mutable {
            button.Create(this, wxID_ANY, std::string{s_butTitles[i++]});
            butSizer->Add(&button, 1, wxEXPAND);
        });
        sizer->Add(butSizer, 1, wxEXPAND);
        this->SetSizer(sizer);
        sizer->Layout();
    }

    MenuOption MainMenu::getOption() const {
        while(currOption.optionId == 0) ;
        return currOption;
    }

    void MainMenu::setOption(const MenuOption option) {
        currOption = option;
    }
}

