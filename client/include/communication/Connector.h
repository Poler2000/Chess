#ifndef CHESS_CONNECTOR_H
#define CHESS_CONNECTOR_H

#include <string>
#include "Message.h"
#include "app/Launcher.h"

class Launcher;

namespace comm {
    class Connector {
    public:
        explicit Connector(unsigned int port);
        void connect() noexcept(false);
        void send(const comm::Message &msg) const noexcept(false);
        void handleConnection();
    private:
        const unsigned int m_port;
        int m_sock;

        Launcher* launcher;
    };
}

#endif //CHESS_CONNECTOR_H
