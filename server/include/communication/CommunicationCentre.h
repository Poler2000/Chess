#ifndef CHESS_COMMUNICATIONCENTRE_H
#define CHESS_COMMUNICATIONCENTRE_H

#include "logic/GameManager.h"
#include "ServerConnector.h"

namespace logic {
    class GameManager;
}

namespace comm {

    class CommunicationCentre : public ServerConnector {
    public:
        CommunicationCentre(logic::GameManager* const manager);
    private:
        constexpr static unsigned int s_defPort = 8080;
        logic::GameManager* const manager;

        void handleConnection(int sockFd) override;
    };
}

#endif //CHESS_COMMUNICATIONCENTRE_H
