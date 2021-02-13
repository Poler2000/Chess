#include <cstring>
#include "communication/CommunicationCentre.h"
#include "communication/CommException.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <communication/Message.h>
#include <fstream>

namespace comm {

    CommunicationCentre::CommunicationCentre() : active(false), manager(nullptr) {}

    CommunicationCentre::CommunicationCentre(logic::GameManager* const manager)
            : active(false), manager(manager) {}

    void CommunicationCentre::init() noexcept(false) {
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

    void CommunicationCentre::startListening(const int maxClients) noexcept(false) {
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
            threads.emplace_back(std::thread(&CommunicationCentre::handleConnection, this, newSocket));
        }
    }

    void CommunicationCentre::stopListening() {
        active = false;
    }

    void CommunicationCentre::handleConnection(int sockFd) {
        while(true) {
            std::cout << "waiting!";
            char buff[256];
            if(read(sockFd, buff, 255) < 0) {
                std::cout << "That's the end for today!\n";
                break;
            }
            std::string file(buff);
            sleep(2);
            std::flush(std::cout);
            std::ifstream is(file);
            cereal::JSONInputArchive archive(is);

            comm::Message msg("");

            archive(msg);
            std::cout << msg.getType() << '\n';
            manager->processMessage(msg, sockFd);
        }
        close(sockFd);
    }

    void CommunicationCentre::send(const Message& msg, int clientFd) {
        std::string file = std::to_string(clientFd);
        std::string newMsg = "../../messages/" + file;
        std::ofstream os(newMsg);
        cereal::JSONOutputArchive archive(os);
        ::send(clientFd, newMsg.c_str(), strlen(newMsg.c_str()), 0);
        archive(msg);
    }

}
