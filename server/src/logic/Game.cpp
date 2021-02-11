#include "../../include/logic/Game.h"

namespace logic {
    const unsigned int logic::Game::getId() const {
        return 0;
    }

    int Game::getPort() {
        return 0;
    }

    bool Game::canAddClient() {
        return false;
    }
}

