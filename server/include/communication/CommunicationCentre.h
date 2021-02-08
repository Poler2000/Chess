#ifndef CHESS_COMMUNICATIONCENTRE_H
#define CHESS_COMMUNICATIONCENTRE_H

#include <netinet/in.h>

namespace comm {
    class CommunicationCentre {
    public:
        void init() noexcept(false);
        void startListening() noexcept(false);
        void stopListening() noexcept(false);
    private:
        struct sockaddr_in address;
        const unsigned int port;
    };
}

#endif //CHESS_COMMUNICATIONCENTRE_H
