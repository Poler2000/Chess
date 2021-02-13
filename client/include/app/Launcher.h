#ifndef CHESS_LAUNCHER_H
#define CHESS_LAUNCHER_H

#include "chessGUI/ChessFrame.h"
#include "chessGUI/MainMenu.h"
#include "communication/Connector.h"
#include <memory>

namespace comm {
    class Connector;
}

class Launcher : public wxApp {
public:
    virtual bool OnInit();
    Launcher();

    void processMessage(const comm::Message &msg, const int clientFd);

private:
    constexpr static unsigned int s_defaultPort = 8080;
    chessGUI::ChessFrame* m_chessFrame;
    chessGUI::MainMenu* m_mainMenu;
    std::unique_ptr<comm::Connector> m_connector;

    void requestNewGame();
};

#endif //CHESS_LAUNCHER_H
