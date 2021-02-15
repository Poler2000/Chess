#include <communication/Message.h>
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

    int Game::getPort() {
        return m_connector->getPort();
    }

    bool Game::canAddClient() {
        return false;
    }

    void Game::processMessage(const comm::Message &msg, const int clientFd) {
        switch (hash(msg.getType().c_str())) {
            case hash("StartGameMsg"):
                /* if(state != GameStates.ONE_PLAYER_READY) {
                     startGame();
                 }*/
                break;
            case hash("PieceSelectedMsg"):
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
        m_connector = std::make_shared<comm::ClientConnector>(this);
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
}

