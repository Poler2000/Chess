#include "logic/GameManager.h"
#include "communication/CommException.h"
#include <iostream>

namespace logic {

    GameManager::GameManager() = default;

    void GameManager::init() {
        createNewGame();
        try {
            communicationCentre.init();
            communicationCentre.startListening(1);
        }
        catch (comm::CommException &ex) {
            std::cout << ex.what();
        }
    }

    void GameManager::createNewGame() {
        games.emplace_back(Game());
    }

    GameManager::~GameManager() = default;
}