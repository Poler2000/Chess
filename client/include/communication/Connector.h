#ifndef CHESS_CONNECTOR_H
#define CHESS_CONNECTOR_H

#include <string>
#include "Message.h"
#include "app/Launcher.h"
#include <memory>

class Launcher;

namespace comm {
    class Connector {
    public:
        Connector(unsigned int port, Launcher* launcher);
        void connect() noexcept(false);
        void send(const comm::Message &msg) const noexcept(false);
        void handleConnection();
    private:
        const unsigned int m_port;
        int m_sock;

        std::shared_ptr<Launcher> launcher;
    };
}

#endif //CHESS_CONNECTOR_H
