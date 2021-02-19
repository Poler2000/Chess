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

    comm::Message newMsg("RegisterMsg");

    m_mainMenu = new chessGUI::MainMenu();
    m_mainMenu->Show(true);

    m_connector->send(newMsg);
    m_chessFrame = new chessGUI::ChessFrame();

    return wxAppConsoleBase::OnInit();
}

void Launcher::processMessage(const comm::Message& msg) {
    switch (hash(msg.getType().c_str())) {
        case hash("GameListMsg"):
            if (m_mainMenu != nullptr) {
                m_mainMenu->fillGameList(msg);
            }
            break;
        case hash("ReconnectMsg"):
            if (msg.hasField("port")) {
                std::cout << "Port: " << msg.getInt("port") << '\n';

                int port = msg.getInt("port");
                sleep(1);
                m_connector.reset();
                m_connector = std::make_unique<comm::Connector>(port, this);
                std::cout << "Ello\n";

                m_connector->connect();
                comm::Message newMsg("RegisterMsg");
                newMsg.addField("role", m_role);
                m_connector->send(newMsg);
                std::cout << "Port: " << msg.getInt("port") << '\n';
                std::cout << "Ello\n";
                m_mainMenu->Disable();

                std::cout << "Showing\n";

                m_chessFrame->Show();

                std::cout << "Shown\n";

                // TODO refactor
                comm::Message startGameMsg("StartGameMsg");
                m_connector->send(startGameMsg);

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
    comm::Message newMsg("CreateGameMsg");
    m_connector->send(newMsg);
}

Launcher::Launcher() : m_connector(std::make_unique<comm::Connector>(s_defaultPort, this)) {}

int Launcher::OnRun() {
    std::thread q(&Launcher::monitorMessages, this);
    std::thread t(&Launcher::processOption, this);
    std::cout << "I'm here\n";
    return wxAppBase::OnRun();
}

void  Launcher::processOption() {
    auto op = m_mainMenu->getOption();

    switch (op.optionId) {
        case chessGUI::MenuOptionValues::CREATE:
            m_role = std::string("player");
            requestNewGame();
            break;
    }
}

void Launcher::addMessageToQueue(std::shared_ptr<comm::Message> msg) {
    msgQueue.push(msg);
}

void Launcher::monitorMessages() {
    while (true) {
        if (!msgQueue.empty()) {
            std::cout << "MESSAGE!\n";
            processMessage(*msgQueue.front());
            std::cout << "MESSAGE END!\n";
            msgQueue.pop();
            std::cout << "MESSAGE POP!\n";
        }
    }
}
