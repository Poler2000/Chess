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
            button.Create(this, 10000 + i, std::string{s_butTitles[i]});
            i++;
            button.Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainMenu::OnButtonClicked, this);
            butSizer->Add(&button, 1, wxEXPAND);
        });
        sizer->Add(butSizer, 1, wxEXPAND);
        this->SetSizer(sizer);
        sizer->Layout();
    }

    MenuOption MainMenu::getOption() const {

        while(currOption.optionId == 0) {
            //std::cout << "w";
            usleep(100);
        }
        std::cout << "\nHello\n";
        return currOption;
    }

    void MainMenu::addToGameList(int i) {
        gameList.Append(std::to_string(i));
    }

    void MainMenu::fillGameList(const comm::Message &message) {
        std::cout << "erer\n";
        auto ids = message.getInts("id");
        std::cout << "erer\n";
        std::for_each(ids.begin(), ids.end(), [&](int val){
            addToGameList(val);
        });
    }

    void MainMenu::OnButtonClicked(wxCommandEvent& ev) {
        setOption(MenuOption{ev.GetId() - 9999, 0});
    }

    void MainMenu::setOption(const MenuOption& option) {
        mtx.lock();
        currOption = option;
        std::cout << "changed\n";
        mtx.unlock();
    }

}

