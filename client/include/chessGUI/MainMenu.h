#ifndef CHESS_MAINMENU_H
#define CHESS_MAINMENU_H

#include <wx/wxprec.h>
#include <string>
#include <array>
#include "ChessField.h"
#include "MenuOption.h"
#include <mutex>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "../../../chessCommon/include/communication/Message.h"

#endif

namespace chessGUI {
    class MainMenu : public wxFrame {
    public:
        MainMenu();
        [[nodiscard]] MenuOption getOption() const;

        void addToGameList(int i);

        void fillGameList(const comm::Message &message);

    private:
        wxDECLARE_EVENT_TABLE();
        constexpr static std::string_view s_butTitles[] = {"Create Game", "Join Game", "Watch as spectator", "Load Replay"};
        constexpr static char s_defaultTitle[] = "Hello Chess!";
        constexpr static unsigned int s_defWidth = 960;
        constexpr static unsigned int s_defHeight = 720;
        constexpr static int s_defXPos = 10;
        constexpr static int s_defYPos = 10;

        std::array<wxButton, 4> buttons;
        wxListBox gameList;
        std::mutex mtx;
        MenuOption currOption{0, 0};

        void OnButtonClicked(wxCommandEvent &ev);
        void setOption(const MenuOption& option);
    };
}

#endif //CHESS_MAINMENU_H
