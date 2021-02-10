#ifndef CHESS_COMMUNICATIONCENTRE_H
#define CHESS_COMMUNICATIONCENTRE_H

#include "logic/GameManager.h"
#include <netinet/in.h>
#include <memory>

namespace logic {
    class GameManager;
}

namespace comm {

    class CommunicationCentre {
    public:
        CommunicationCentre();

        CommunicationCentre(const logic::GameManager* const manager);

        void init() noexcept(false);
        void startListening(int maxClients) noexcept(false);
        void stopListening();
    private:
        struct sockaddr_in m_address;
        const unsigned int m_port = 8080;
        const logic::GameManager* const manager;
        int serverFd;
        const int m_option = 1;
        volatile bool active;

        void handleConnection(int sockFd);
    };
}

#endif //CHESS_COMMUNICATIONCENTRE_H
