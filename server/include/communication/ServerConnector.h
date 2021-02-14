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
        virtual ~ServerConnector() = default;;

        void init() noexcept(false);
        void startListening(int maxClients) noexcept(false);
        void stopListening();
        void send(const comm::Message& msg, int clientFd);
    private:
        struct sockaddr_in m_address;
        const unsigned int m_port;
        int serverFd;
        const int m_option = 1;
        std::atomic_bool active;
        std::vector<std::thread> threads;

        virtual void handleConnection(int sockFd) = 0;
    };
}

#endif //CHESS_SCONNECTOR_H
