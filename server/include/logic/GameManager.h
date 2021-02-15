#ifndef CHESS_GAMEMANAGER_H
#define CHESS_GAMEMANAGER_H

#include "Game.h"
#include "communication/CommunicationCentre.h"
#include <vector>
#include <thread>
#include <mutex>
#include <communication/Message.h>

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
        void processMessage(const comm::Message &msg, const int clientFd);
        void addMessageToQueue(const comm::Message& msg, const int clientFd);
        void monitorMessages();
    private:
        constexpr static uint32_t s_maxClients = 16;
        void createNewGame(const int clientFd);
        void addClientToGame(int gameId, int clientFd);
        void addAsSpectator(int gameId, int clientFd);
        Game& getGameById(uint32_t id);
        std::mutex gmMutex;
        std::vector<Game> m_games;
        std::unique_ptr<comm::CommunicationCentre> m_communicationCentre;
        std::queue<std::pair<comm::Message, const int>> m_msgQueue;



        void prepareAndSendListOfGames(const int fd);
    };
}

#endif //CHESS_GAMEMANAGER_H
