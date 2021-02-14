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


    m_mainMenu = new chessGUI::MainMenu();
    m_mainMenu->Show(true);

    m_connector->send(newMsg);
    std::thread t(&comm::Connector::handleConnection, *m_connector);
    t.detach();
    std::cout << "hey\n";
    //m_chessFrame = new chessGUI::ChessFrame();
   // m_chessFrame->Show();

    return wxAppConsoleBase::OnInit();
}

void Launcher::processMessage(const comm::Message& msg, const int clientFd) {
    switch(hash(msg.getType().c_str())) {
        case hash("GameListMsg"):
            std::cout << "Ej\n";
            if (m_mainMenu == nullptr) {
                std::cout << "Null here";
            }
            else {
                std::cout << "Not Null here";
                m_mainMenu->fillGameList(msg);
            }
            requestNewGame();
            break;
        case hash("ReconnectMsg"):
            if (msg.hasField("port")) {
                m_connector = std::make_unique<comm::Connector>(msg.getInt("port"), this);
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

void Launcher::requestNewGame() {
    std::cout << "new game!\n";
    sleep(2);
    comm::Message newMsg("CreateGameMsg");
    m_connector->send(newMsg);
}

Launcher::Launcher() : m_connector(std::make_unique<comm::Connector>(s_defaultPort, this)) {}

int Launcher::OnRun() {
    std::cout << "On run\n";

    std::thread t(&Launcher::processOption, this);

    return wxAppBase::OnRun();
}

void  Launcher::processOption() {
    auto op = m_mainMenu->getOption();
    std::cout << "Got option!\n";
    std::cout << op.optionId << '\n';
    switch (op.optionId) {
        case chessGUI::MenuOptionValues::CREATE:
            requestNewGame();
            break;
    }
}
