#include "logic/GameManager.h"
#include "communication/CommException.h"
#include <iostream>

namespace logic {

    GameManager::GameManager()
        : m_communicationCentre(new comm::CommunicationCentre(this)) {}

    GameManager::~GameManager() = default;

    void GameManager::init() {
        try {
            m_communicationCentre->init();
            m_communicationCentre->startListening(s_maxClients);
        }
        catch (comm::CommException& ex) {
            std::cout << ex.what() << '\n';
        }
    }

    void GameManager::createNewGame(const int clientFd) {
        m_games.emplace_back(Game());
        m_communicationCentre->sendPortInfo(m_games.back().getPort(), clientFd);
    }

    void GameManager::run() {
        while(true) {

        }
    }

    void GameManager::processMessage(const std::string& msg, const int clientFd) {
        gmMutex.lock();

        gmMutex.unlock();
    }

    void GameManager::processMessage(const char *msg, const int clientFd) {
        std::string m{msg};
        processMessage(m, clientFd);
    }

    void GameManager::addClientToGame(const int gameId, const int clientFd) {
        auto g = getGameById(gameId);
        if(g.canAddClient()) {
            m_communicationCentre->sendPortInfo(g.getPort(), clientFd);
        }
    }


    void GameManager::addAsSpectator(const int gameId, const int clientFd) {
        auto g = getGameById(gameId);
        m_communicationCentre->sendPortInfo(g.getPort(), clientFd);
    }

    // TODO what if no game matches?
    Game& GameManager::getGameById(const uint32_t id) {
        auto k = std::find_if(m_games.begin(), m_games.end(),
                              [=](const Game & g) -> bool { return g.getId() == id; });
        return *k;
    }


}