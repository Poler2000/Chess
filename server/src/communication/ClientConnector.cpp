#include "communication/ClientConnector.h"
#include <fstream>
#include <unistd.h>

namespace comm {
    ClientConnector::ClientConnector(logic::Game *const game)
        : ServerConnector(generateId() + 8080), game(game) {}

    void ClientConnector::handleConnection(int sockFd) {
        std::cout << "HANDLING\n";
        while(true) {
            std::cout << "waiting!";
            char buff[256];
            if(read(sockFd, buff, 255) < 0) {
                break;
            }
            std::cout << buff << '\n';
            std::string file(buff);
            std::ifstream is(file);
            cereal::JSONInputArchive archive(is);

            comm::Message msg("");
            archive(msg);
            std::cout << "Got msg: " << msg.getType() << '\n';
            game->addMessageToQueue(msg, sockFd);
        }
        close(sockFd);
    }

    uint32_t ClientConnector::generateId() {
        static uint32_t counter = 1;
        s_mtx.lock();
        uint32_t result = counter;
        counter++;
        s_mtx.unlock();
        return result;
    }
}

