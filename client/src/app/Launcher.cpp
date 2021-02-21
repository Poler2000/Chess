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
    m_chessFrame = new chessGUI::ChessFrame(std::shared_ptr<Launcher>(this));

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

                int port = msg.getInt("port");
                sleep(1);
                m_connector.reset();
                m_connector = std::make_unique<comm::Connector>(port, this);

                m_connector->connect();
                comm::Message newMsg("RegisterMsg");
                newMsg.addField("role", m_role);
                m_connector->send(newMsg);
                m_mainMenu->Disable();

                m_chessFrame->Show();

                // TODO refactor
                comm::Message startGameMsg("StartGameMsg");
                m_connector->send(startGameMsg);

            }
            break;
        case hash("GameStateMsg"):
            m_chessFrame->resetFigures();
            try {
                auto figures = msg.getFigureConfig();
                for (auto& f : figures) {
                    m_chessFrame->placeFigure(f.id, f.pieceType, f.colourId, f.x, f.y);
                }
            }
            catch (comm::CommException& ex) {
                std::cout << ex.what() << '\n';
            }
            break;
        case hash("PossibleMovesMsg"):
            handlePositions(msg);
            break;
        default:
            std::cout << "Incorrect message type\n";
            break;
    }
}

void Launcher::requestNewGame() {
    comm::Message newMsg("CreateGameMsg");
    m_connector->send(newMsg);
}

Launcher::Launcher() : m_connector(std::make_unique<comm::Connector>(s_defaultPort, this)) {}

int Launcher::OnRun() {
    std::thread q(&Launcher::monitorMessages, this);
    std::thread t(&Launcher::processOption, this);
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
            processMessage(*msgQueue.front());
            msgQueue.pop();
        }
    }
}

void Launcher::processFigureSelection(const int id) {
    comm::Message msg("PieceSelectedMsg");
    msg.addField("id", id);
    m_connector->send(msg);
}

void Launcher::handlePositions(const comm::Message &msg) {
    auto positions = msg.getPositions();
    for (auto& p : positions) {
        m_chessFrame->enableMoveTo(p.x, p.y);
    }
}

void Launcher::processMove(const int id, const int x, const int y) {
    comm::Message msg("MovedMsg");
    msg.addField("move", structure::Move{id, x, y});
    m_connector->send(msg);
}
