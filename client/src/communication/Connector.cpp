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
    Connector::Connector(unsigned int port) : m_port(port) {}

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

        if (::connect(m_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            throw CommException("Couldn't establish connection");
        }
    }

    void Connector::handleConnection() {
        std::cout << "waiting!";
        std::flush(std::cout);
        sleep(3);

        while(true) {
            std::cout << "doing!";
            std::flush(std::cout);
            sleep(3);
            char buff[256];
            if(read(m_sock, buff, 255) < 0) {
                std::cout << "That's the end for today!\n";
                std::cout << "doinqfefqeg!";
                std::flush(std::cout);
                sleep(1);
                break;
            }
            std::cout << "doingqrfe!";
            std::flush(std::cout);
            sleep(3);
            std::string file(buff);
            sleep(2);
            std::flush(std::cout);
            std::ifstream is(file);
            cereal::JSONInputArchive archive(is);

            comm::Message msg("");

            archive(msg);
            std::cout << msg.getType() << '\n';
            launcher->processMessage(msg, m_sock);
        }
        close(m_sock);
    }

    void Connector::send(const Message& msg) const noexcept(false) {
        std::cout << msg.getType() << '\n';
        std::string file = std::to_string(m_sock);
        std::string newMsg = "../../messages/" + file;
        std::ofstream os(newMsg);
        ::send(m_sock, newMsg.c_str(), strlen(newMsg.c_str()), 0);
        cereal::JSONOutputArchive archive(os);
        archive(msg);
    }
}