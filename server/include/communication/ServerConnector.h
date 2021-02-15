#ifndef CHESS_SCONNECTOR_H
#define CHESS_SCONNECTOR_H

#include <atomic>
#include <memory>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include "Message.h"
#include "CommException.h"

namespace comm {
    class ServerConnector {
    public:
        explicit ServerConnector(int port);
        ServerConnector();
        virtual ~ServerConnector() = default;;

        void init() noexcept(false);
        void startListening(int maxClients) noexcept(false);
        void stopListening();
        void send(const comm::Message& msg, int clientFd);
        void closeConnection(int clientFd);
        int getPort() const;
    private:
        struct sockaddr_in m_address;
        unsigned int m_port;
        int serverFd;
        const int m_option = 1;
        std::atomic_bool active;
        std::vector<std::pair<std::thread, int>> threads;

        virtual void handleConnection(int sockFd) = 0;
    };
}

#endif //CHESS_SCONNECTOR_H
