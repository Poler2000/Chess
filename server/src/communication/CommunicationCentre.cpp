#include "communication/CommunicationCentre.h"
#include "communication/CommException.h"
#include <unistd.h>
#include <communication/Message.h>
#include <fstream>

namespace comm {

    CommunicationCentre::CommunicationCentre(logic::GameManager* const manager)
        : manager(manager), ServerConnector(s_defPort) {}

    void CommunicationCentre::handleConnection(int sockFd) {
        while(true) {
            std::cout << "waiting!";
            char buff[256];
            if(read(sockFd, buff, 255) < 0) {
                std::cout << "That's the end for today!\n";
                break;
            }
            std::cout << buff << '\n';
            std::string file(buff);
            std::ifstream is(file);
            cereal::JSONInputArchive archive(is);

            comm::Message msg("");

            archive(msg);
            std::cout << msg.getType() << '\n';
            manager->processMessage(msg, sockFd);
        }
        close(sockFd);
    }

}
