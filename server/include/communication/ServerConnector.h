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

        /**
         * @param port port to connect to
         */
        explicit ServerConnector(int port);
        ServerConnector();
        virtual ~ServerConnector() = default;;

        /**
         * Creates server socket and binds
         * it to m_port if it was previously specified
         * throws comm::CommException on any
         * encountered problem
         */
        void init() noexcept(false);

        /**
         * Enables connection accepting. Enters loop that executes until
         * until stopListening() is called and create new thread for every
         * accepted connection.
         * throws comm::CommException
         * @param maxClients max number of clients
         */
        void startListening(int maxClients) noexcept(false);

        /**
         * Makes connector ignore any new connection request.
         * Doesn't affect existing connections.
         */
        void stopListening();

        /**
         * Serialize given message and writes it to file in JSON format.
         * The path to file is sent through socket
         * @param msg message to send
         * @param clientFd file descriptor of receiver
         */
        void send(const comm::Message& msg, int clientFd);

        /**
         * Closes specified connection
         * @param clientFd file descriptor of client to close connection with
         */
        void closeConnection(int clientFd);

        /**
         * @return m_port - port the connector is listening on.
         */
        [[nodiscard]] int getPort() const;
    private:
        struct sockaddr_in m_address;
        unsigned int m_port;
        int serverFd;
        const int m_option = 1;

        std::atomic_bool active;
        std::vector<std::pair<std::thread, int>> threads;

        /**
         * Handles new connection.
         * @param sockFd file descriptor of client
         */
        virtual void handleConnection(int sockFd) = 0;
    };
}

#endif //CHESS_SCONNECTOR_H
