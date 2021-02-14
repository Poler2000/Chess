#include <communication/Message.h>
#include <fstream>
#include "communication/ServerConnector.h"

namespace comm {
    void ServerConnector::init() noexcept(false) {
        if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            throw CommException("Unable to create file descriptor");
        }

        if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &m_option, sizeof(m_option))) {
            throw CommException("Unable to set socket options");
        }
        m_address.sin_family = AF_INET;
        m_address.sin_addr.s_addr = INADDR_ANY;
        m_address.sin_port = htons(m_port);

        if (bind(serverFd, (struct sockaddr *)&m_address,
                 sizeof(m_address))<0) {
            throw CommException("Unable to bind socket to port");
        }
    }

    void ServerConnector::startListening(const int maxClients) noexcept(false) {
        if (listen(serverFd, maxClients) < 0) {
            throw CommException("Couldn't start listening");
        }
        active = true;

        int addrLen = sizeof(m_address);
        puts("Waiting for connections ...");

        while (active) {
            int newSocket;
            if ((newSocket = accept(serverFd, (struct sockaddr *)&m_address, (socklen_t*)&addrLen)) < 0) {
                throw comm::CommException("Couldn't accept connection");
            }
            else {
                std::cout << "connected\n";
            }
            threads.emplace_back(std::thread(&ServerConnector::handleConnection, this, newSocket));
        }
    }

    void ServerConnector::stopListening() {
        active = false;
    }

    void ServerConnector::send(const Message& msg, int clientFd) {
        std::cout << msg.getType() << '\n';
        std::string file = std::to_string(clientFd);
        std::string newMsg = "../../messages/" + file;
        std::ofstream os(newMsg);
        cereal::JSONOutputArchive archive(os);
        archive(msg);
        ::send(clientFd, newMsg.c_str(), strlen(newMsg.c_str()), 0);
    }

    ServerConnector::ServerConnector(int port)
        : active(false), m_port(port) {}
}