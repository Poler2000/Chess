#include <thread>
#include "app/Launcher.h"
#include "communication/CommException.h"

wxIMPLEMENT_APP(Launcher);

constexpr uint64_t mix(char m, uint64_t s) {
    return ((s<<7) + ~(s>>3)) + ~m;
}

constexpr uint64_t hash(const char * m) {
    return (*m) ? mix(*m,hash(m+1)) : 0;
}

bool Launcher::OnInit() {
    try {
        m_connector->connect();
    }
    catch (comm::CommException& ex) {
        std::cout << ex.what();
    }
    std::cout << "hey\n";

    comm::Message newMsg("RegisterMsg");

    std::cout << "hey\n";

    m_connector->send(newMsg);
    std::thread t(&comm::Connector::handleConnection, *m_connector);
    t.detach();
    std::cout << "hey\n";

    m_mainMenu = new chessGUI::MainMenu();
    m_mainMenu->Show();
    //m_chessFrame = new chessGUI::ChessFrame();
   // m_chessFrame->Show();
    //m_mainMenu->getOption();

    return wxAppConsoleBase::OnInit();
}

void Launcher::processMessage(const comm::Message& msg, const int clientFd) {
    switch(hash(msg.getType().c_str())) {
        case hash("GameListMsg"):
            requestNewGame(clientFd);
            break;
        case hash("ReconnectMsg"):
            if (msg.hasField("port")) {
                m_connector = std::make_unique<comm::Connector>(msg.getInt("port"));
            }
            break;
        case hash("GameStateMsg"):
            break;
        case hash("PossibleMovesMsg"):
            break;
        default:
            std::cout << "Incorrect message type\n";
            break;
    }
    std::cout << "Received\n";
}

void Launcher::requestNewGame(const int clientFd) {
    std::cout << "new game!\n";
    sleep(2);
    comm::Message newMsg("CreateGameMsg");
    m_connector->send(newMsg);
}

Launcher::Launcher() : m_connector(std::make_unique<comm::Connector>(s_defaultPort)) {}
