#include <communication/Message.h>

#include <memory>
#include "../../include/logic/Game.h"

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
            if (++counter > 1) {
                return false;
            }
        }
        return true;
    }

    void Game::processMessage(const comm::Message &msg, const int clientFd) {
        switch (hash(msg.getType().c_str())) {
            case hash("StartGameMsg"):
                 if(gameState > GameStates::NO_PLAYERS) {
                     startGame();
                 }
                break;
            case hash("PieceSelectedMsg"):
                int pieceId = msg.getInt("id");
                for (auto& p : m_players) {
                    if (m_turnOfColour == p->getColour()) {
                        auto possibilities = std::find_if(p->getFigures().begin(), p->getFigures().end(), [pieceId](auto& piece) {
                            return piece->getId() == pieceId;
                        })->get()->getPossibleMovements(m_fields);
                        comm::Message newMsg("PossibleMovesMsg");
                        std::for_each(possibilities.begin(), possibilities.end(), [&](int id){
                            newMsg.addField(":")
                        });
                        break;
                    }
                }
                break;
            case hash("MoveMsg"):
                break;
            default:
                std::cout << "Incorrect message type\n";
                break;
        }
        std::cout << "Received\n";
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

    }
}

