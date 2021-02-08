#ifndef CHESS_COMMUNICATIONCENTRE_H
#define CHESS_COMMUNICATIONCENTRE_H

#include <netinet/in.h>

namespace comm {
    class CommunicationCentre {
    public:
        CommunicationCentre();
        void init() noexcept(false);
    private:
        struct sockaddr_in m_address;
        const unsigned int m_port = 8080;
        int serverFd;
        const int m_option = 1;
    };
}

#endif //CHESS_COMMUNICATIONCENTRE_H
