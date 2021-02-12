#include <communication/Connector.h>
#include "communication/CommException.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "communication/Message.h"
#include <fstream>


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

    void Connector::send(const Message& msg) const noexcept(false) {
        //::send(m_sock , msg.c_str() , msg.length() , 0);
        {
            std::cout << "hey\n";
            std::string file = std::to_string(m_sock);
            std::ofstream os("file.dat");
            cereal::JSONOutputArchive archive(os);
            archive(msg);
            std::cout << "hey0\n";
        }
        ::send(m_sock , " " , strlen(" ") , 0);
        printf("Hello message sent\n");
    }
}