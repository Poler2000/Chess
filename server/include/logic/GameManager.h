#ifndef CHESS_GAMEMANAGER_H
#define CHESS_GAMEMANAGER_H

#include "Game.h"
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
    };
}

#endif //CHESS_GAMEMANAGER_H
