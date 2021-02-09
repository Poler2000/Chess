#include <cstring>
#include "communication/CommunicationCentre.h"
#include "communication/CommException.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

namespace comm {

    CommunicationCentre::CommunicationCentre() : active(false) {}

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

        while (true) {
            int newSocket;
            if ((newSocket = accept(serverFd, (struct sockaddr *)&m_address, (socklen_t*)&addrLen)) < 0) {
                throw comm::CommException("Couldn't accept connection");
            }

            handleConnection(newSocket);
        }


    }

    void CommunicationCentre::stopListening() {
        active = false;
    }

    void CommunicationCentre::handleConnection(int sockFd) {
        char test[256];
        bzero(test, 256);
        while(true)
        {
            bzero(test, 256);
            int n = read(sockFd, test, 255);
            if (n < 0) {
                break;
            }
            printf("Here is the message: %s\n",test);
        }
        close(sockFd);
    }
}
