#ifndef CHESS_CONNECTOR_H
#define CHESS_CONNECTOR_H

#include <string>
#include "Message.h"
#include "app/Launcher.h"
#include <memory>
#include <thread>

class Launcher;

namespace comm {
    class Connector {
    public:
        Connector(unsigned int port, Launcher* launcher);
        ~Connector();
        void connect() noexcept(false);
        void send(const comm::Message &msg) const noexcept(false);
        void handleConnection();
    private:
        const unsigned int m_port;
        int m_sock;
        volatile bool active;

        std::shared_ptr<Launcher> launcher;
        std::thread handler;

        void stopListening();
    };
}

#endif //CHESS_CONNECTOR_H
