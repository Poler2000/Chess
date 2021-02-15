#ifndef CHESS_CLIENTCONNECTOR_H
#define CHESS_CLIENTCONNECTOR_H

#include "logic/Game.h"
#include "ServerConnector.h"

namespace logic {
    class Game;
}

namespace comm {

    class ClientConnector : public ServerConnector {
    public:
        explicit ClientConnector(logic::Game *const game);
    private:
        logic::Game* const game;

        void handleConnection(int sockFd) override;
    };
}


#endif //CHESS_CLIENTCONNECTOR_H
