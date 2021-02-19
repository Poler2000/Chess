#include <communication/Connector.h>
#include "communication/CommException.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "communication/Message.h"

#include <fstream>
#include <thread>

namespace comm {
    Connector::Connector(unsigned int port, Launcher* launcher)
        : m_port(port), launcher(std::shared_ptr<Launcher>(launcher)) {}

    void Connector::connect() noexcept(false) {
        struct sockaddr_in serv_addr{};
        if ((m_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            throw CommException("Couldn't create socket");
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(m_port);

        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            throw CommException("Invalid address");
        }
        std::cout << "QWERTY\n";

        if (::connect(m_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Connect");
            throw CommException("Couldn't establish connection");
        }
        std::cout << "QWERTY\n";

        handler = std::thread(&Connector::handleConnection, this);
    }

    void Connector::handleConnection() {
        active = true;

        while(active) {
            char buff[256];
            std::cout << "Waiting for input!\n";
            if(read(m_sock, buff, 255) < 0) {
                break;
            }

            std::cout << "received input!\n";
            std::cout << buff << '\n';
            std::flush(std::cout);
            usleep(100);

            std::string file(buff);
            std::ifstream is(file);
            cereal::JSONInputArchive archive(is);


            std::shared_ptr<comm::Message> msg = std::make_shared<comm::Message>("");

            archive(*msg);
            std::cout << "Msg type: " << msg->getType() << '\n';

            launcher->addMessageToQueue(msg);

            if (msg->getType() == "ReconnectMsg") {
                std::cout << "Reconnect\n";
                break;
            }
        }
    }

    void Connector::send(const Message& msg) const noexcept(false) {
        std::cout << "I'm sending " << msg.getType() << '\n';
        std::string file = std::to_string(m_sock);
        std::string newMsg = "../../messages/" + file;
        std::ofstream os(newMsg);
        cereal::JSONOutputArchive archive(os);
        archive(msg);
        ::send(m_sock, newMsg.c_str(), strlen(newMsg.c_str()), 0);
    }

    Connector::~Connector() {
        std::cout << "closing!\n";
        close(m_sock);
        handler.join();
        std::cout << "closing!\n";
    }

    void Connector::stopListening() {
        active = false;
    }
}