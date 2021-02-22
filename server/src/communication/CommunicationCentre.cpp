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
            if (read(sockFd, buff, 255) < 0) {
                break;
            }
            if (buff[0] == '\0') {
                continue;
            }
            std::cout << buff << '\n';
            std::string file(buff);
            try {
                std::ifstream is(file);
                cereal::JSONInputArchive archive(is);

                comm::Message msg("");

                archive(msg);
                std::cout << "Got msg: " << msg.getType() << '\n';
                manager->addMessageToQueue(msg, sockFd);
                if (msg.getType() == "CreateGameMsg") {
                    return;
                }
            }
            catch (cereal::RapidJSONException& ex) {
                std::cout << ex.what();
            }

        }
        close(sockFd);
    }

}
