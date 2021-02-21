#ifndef CHESS_LAUNCHER_H
#define CHESS_LAUNCHER_H

#include "chessGUI/ChessFrame.h"
#include "chessGUI/MainMenu.h"
#include "communication/Connector.h"
#include <memory>
#include <queue>
#include <memory>

namespace comm {
    class Connector;
}
namespace chessGUI {
    class ChessFrame;
}

class Launcher : public wxApp {
public:
    virtual bool OnInit();
    virtual int OnRun();

    Launcher();

    void processMessage(const comm::Message &msg);
    void addMessageToQueue(std::shared_ptr<comm::Message> msg);

    void monitorMessages();
    void processFigureSelection(int id);
    void processMove(int id, int x, int y);

private:
    constexpr static unsigned int s_defaultPort = 8080;
    chessGUI::ChessFrame* m_chessFrame;
    chessGUI::MainMenu* m_mainMenu;
    std::unique_ptr<comm::Connector> m_connector;
    std::queue<std::shared_ptr<comm::Message>> msgQueue;

    void requestNewGame();

    void processOption();

    std::basic_string<char> m_role;

    void handlePositions(const comm::Message &msg);
};

#endif //CHESS_LAUNCHER_H
