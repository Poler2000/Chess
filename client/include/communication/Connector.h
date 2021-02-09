#ifndef CHESS_CONNECTOR_H
#define CHESS_CONNECTOR_H

#include <string>

namespace comm {
    class Connector {
    public:
        Connector(unsigned int port);
        void connect() noexcept(false);
        void send(std::string& msg) const noexcept(false);
    private:
        const unsigned int m_port;
        int m_sock;
    };
}

#endif //CHESS_CONNECTOR_H
