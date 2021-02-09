#ifndef CHESS_GAMEMANAGER_H
#define CHESS_GAMEMANAGER_H

#include "Game.h"
#include "communication/CommunicationCentre.h"
#include <vector>
#include <thread>

namespace logic {
    class GameManager {
    public:
        GameManager();
        ~GameManager();
        void init();

    private:
        void createNewGame();
        std::vector<Game> games;
        comm::CommunicationCentre communicationCentre;
    };
}

#endif //CHESS_GAMEMANAGER_H
