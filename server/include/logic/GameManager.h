#ifndef CHESS_GAMEMANAGER_H
#define CHESS_GAMEMANAGER_H

#include "Game.h"
#include "communication/CommunicationCentre.h"
#include <vector>
#include <thread>

namespace comm {
    class CommunicationCentre;
}

namespace logic {
    class GameManager {
    public:
        GameManager();
        ~GameManager();
        void init();
        void run();
        void processMessage(std::string& msg, int clientFd);
    private:
        constexpr static uint32_t s_maxClients = 16;
        void createNewGame();
        void addClientToGame(int gameId, int clientFd);
        void addAsSpectator(int gameId, int clientFd);
        Game& getGameById();

        std::vector<Game> m_games;
        std::unique_ptr<comm::CommunicationCentre> m_communicationCentre;
    };
}

#endif //CHESS_GAMEMANAGER_H
