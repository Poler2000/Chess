#include <communication/Message.h>

#include <memory>
#include "../../include/logic/Game.h"
#include "structure/FigureData.h"

namespace logic {
    constexpr uint64_t mix(char m, uint64_t s) {
        return ((s << 7) + ~(s >> 3)) + ~m;
    }

    constexpr uint64_t hash(const char *m) {
        return (*m) ? mix(*m, hash(m + 1)) : 0;
    }

    int logic::Game::getId() const {
        return m_id;
    }

    int Game::getPort() const {
        return m_connector->getPort();
    }

    bool Game::canAddClient() const {
        int counter = 0;
        for (auto& p : m_players) {
            if (p->isPlaying()) {
                if (++counter > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    void Game::processMessage(const comm::Message &msg, const int clientFd) {
        switch (hash(msg.getType().c_str())) {
            case hash("RegisterMsg"):
                handleRegister(msg.getString("role"), clientFd);
                break;
            case hash("StartGameMsg"):
                if (gameState > GameStates::NO_PLAYERS) {
                    startGame();
                 }
                break;
            case hash("PieceSelectedMsg"):
                processFigureSelection(msg.getInt("id"), clientFd);
                break;
            case hash("MoveMsg"):
                processMoveMsg(msg.getMove());
                break;
            default:
                std::cout << "Incorrect message type\n";
                break;
        }
    }

    void Game::init() {
        gameState = GameStates::NO_PLAYERS;
        m_connector = std::make_shared<comm::ClientConnector>(this);
        createFields();
        m_moveValidator = std::make_unique<MoveValidator>(m_fields);
        m_connector->init();
        std::thread t(&Game::monitorMessages, this);
        t.detach();
        std::thread q(&comm::ServerConnector::startListening, m_connector, 8);
        q.detach();
    }

    Game::Game() : m_id(0) {}

    Game::Game(Game const &game) : m_id(game.getId()) {
    }

    void Game::monitorMessages() {
        while (true) {
            if (!m_msgQueue.empty()) {
                processMessage(m_msgQueue.front().first, m_msgQueue.front().second);
                m_msgQueue.pop();
            }
        }
    }

    void Game::addMessageToQueue(const comm::Message &msg, const int clientFd) {
        m_msgQueue.push(std::make_pair(msg, clientFd));
    }

    void Game::createFields() {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                m_fields.emplace_back(std::make_shared<structure::Field>(x, y));
            }
        }
    }

    void Game::runGame() {
        while (gameState < GameStates::RUNNING) ;
        while (gameState ==  GameStates::RUNNING) {
            for (auto& p : m_players) {
                if (m_turnOfColour == p->getColour()) {
                    auto move = p->getMove();
                    std::cout << "got move!\n";

                    if (m_moveValidator->isValid(move)) {
                        update(move);
                    }
                    break;
                }
            }
            checkWinConditions();
        }
    }

    void Game::checkWinConditions() {

    }

    void Game::startGame() {
        if (gameState == GameStates::ONE_PLAYER_READY) {
            m_players.emplace_back(new ComputerPlayer(structure::PieceFactory::getRedId()));
        }
        std::for_each(m_players.begin(), m_players.end(), [&](auto& p) {
            if (p->getColour() == structure::PieceFactory::getBlueId()) {
                p->setFigures(structure::PieceFactory::getBlue(m_fields));
            }
            else if (p->getColour() == structure::PieceFactory::getRedId()) {
                p->setFigures(structure::PieceFactory::getRed(m_fields));
            }
        });
        m_turnOfColour = structure::PieceFactory::getBlueId();
        gameState = GameStates::RUNNING;
        processGameState();
    }

    void Game::update(structure::Move move) {
        std::cout << "Moving!\n";

        auto figures = getAllFigures();
        auto figToMove = std::find_if(figures.begin(), figures.end(), [&](auto& f){
            return move.pieceId == f->getId();
        });

        std::find_if(m_fields.begin(), m_fields.end(), [&](auto& f){
            return figToMove->get()->getX() == f->getX() &&
                    figToMove->get()->getX() == f->getY();
        })->get()->setOccupied(figToMove->get()->getColour());

        std::find_if(m_fields.begin(), m_fields.end(), [&](auto& f){
            return move.destX == f->getX() &&
                    move.destY == f->getY();
        })->get()->setOccupied(figToMove->get()->getColour());
        figToMove->get()->move(move.destX, move.destY);
    }

    void Game::processFigureSelection(const int pieceId, const int clientFd) {
        for (auto& p : m_players) {
            auto figures = p->getFigures();
            if (m_turnOfColour == p->getColour()) {
                auto it = std::find_if(figures.begin(), figures.end(), [pieceId](auto& piece) {
                    return piece->getId() == pieceId;
                });
                if (it >= figures.end()) {
                    continue;
                }
                auto possibilities = it->get()->getPossibleMovements(m_fields);

                comm::Message newMsg("PossibleMovesMsg");
                std::for_each(possibilities.begin(), possibilities.end(), [&](structure::chessPoint point) {
                    newMsg.addField("position", point);
                });
                m_connector->send(newMsg, clientFd);
                break;
            }
        }
    }

    void Game::processGameState() {
        comm::Message msg("GameStateMsg");
        comm::Message msg2("GameStateMsg");

        std::vector<std::shared_ptr<structure::Figure>> figures;
        std::for_each(m_players.begin(), m_players.end(), [&](auto& p){
            auto figs = p->getFigures();
            figures.insert(figures.end(), figs.begin(), figs.end());
        });

        msg.addField("gameId", (int)m_id);
        msg2.addField("gameId", (int)m_id);
        msg.addField("players", (int)m_players.size());
        msg2.addField("players", (int)m_players.size());
        msg.addField("gameState", (int)gameState);
        msg2.addField("gameState", (int)gameState);

        std::for_each(figures.begin(), figures.end(), [&](auto& f) {
            msg.template addField("figure", structure::FigureData(f));
            msg2.template addField("figure", structure::FigureData(f));
        });
        msg.addField("yourTurn", 0);
        msg2.addField("yourTurn", 1);

        std::for_each(m_players.begin(), m_players.end(), [&](auto& p) {
            if (m_turnOfColour == p->getColour()) {
                m_connector->send(msg2, p->getFd());
            }
            else {
                m_connector->send(msg, p->getFd());
            }
        });
    }

    void Game::handleRegister(const std::string& role, const int fd) {
        static bool isThereFirst = false;
        if (role == "player") {
            m_players.emplace_back(new HumanPlayer(true, fd, isThereFirst ?
                structure::PieceFactory::getRedId() : structure::PieceFactory::getBlueId()));
            if (isThereFirst) {
                gameState = GameStates::TWO_PLAYERS_READY;
            }
            else {
                gameState = GameStates::ONE_PLAYER_READY;
            }
            isThereFirst = true;
        }
        else if (role == "spectator") {
            m_players.emplace_back(new HumanPlayer(false, fd, 0));
        }
    }

    std::vector<std::shared_ptr<structure::Figure>> Game::getAllFigures() {
        std::vector<std::shared_ptr<structure::Figure>> figures;
        std::for_each(m_players.begin(), m_players.end(), [&](auto& p){
            auto figs = p->getFigures();
            figures.insert(figures.end(), figs.begin(), figs.end());
        });
        return figures;
    }

    void Game::processMoveMsg(structure::Move move) {
        std::cout << move.pieceId << " Move processing!\n";
        for (auto& p : m_players) {
            auto figures = p->getFigures();
            auto it = std::find_if(figures.begin(), figures.end(), [&](auto& f) {
                return f->getId() == move.pieceId;
            });
            if (it < figures.end()) {
                std::cout << "Move setting!\n";
                p->setMove(move);
            }
        }
    }
}

