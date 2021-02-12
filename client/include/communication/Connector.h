#ifndef CHESS_CONNECTOR_H
#define CHESS_CONNECTOR_H

#include <string>
#include "Message.h"

namespace comm {
    class Connector {
    public:
        explicit Connector(unsigned int port);
        void connect() noexcept(false);
        void send(const comm::Message &msg) const noexcept(false);
    private:
        const unsigned int m_port;
        int m_sock;
    };
}

#endif //CHESS_CONNECTOR_H
