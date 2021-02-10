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
            std::cout << ex.what();
        }
    }

    void GameManager::createNewGame() {
        m_games.emplace_back(Game());
    }

    void GameManager::run() {

    }


}