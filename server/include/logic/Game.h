#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "communication/Message.h"
#include "communication/ClientConnector.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "AbstractPlayer.h"
#include "MoveValidator.h"
#include <queue>
#include <mutex>
#include <algorithm>

namespace comm {
   class ClientConnector;
}

namespace logic {
    enum GameStates {
        NO_PLAYERS,
        ONE_PLAYER_READY,
        TWO_PLAYERS_READY,
        RUNNING,
        ENDED
    };

    class Game {
    public:
        Game();
        Game(Game const& game);

        int getId() const;
        int getPort() const;

        void init();
        void createFields();

        bool canAddClient() const;
        void addMessageToQueue(const comm::Message& msg, const int clientFd);
    private:
        void processMessage(const comm::Message &msg, const int clientFd);
        void monitorMessages();
        void runGame();

        std::vector<std::shared_ptr<AbstractPlayer>> m_players;
        const uint32_t m_id;
        std::mutex m_mtx;
        GameStates gameState;
        std::shared_ptr<comm::ClientConnector> m_connector;
        std::queue<std::pair<comm::Message, const int>> m_msgQueue;
        std::vector<std::shared_ptr<structure::Field>> m_fields;
        std::unique_ptr<MoveValidator> m_moveValidator;
        uint16_t m_turnOfColour;

        void checkWinConditions();

        void startGame();

        void update(structure::Move move);

        void processFigureSelection(const int pieceId, const int clientFd);

        void processGameState();

        void handleRegister(const std::string &role, const int fd);

        std::vector<std::shared_ptr<structure::Figure>> getAllFigures();
    };
}



#endif //CHESS_GAME_H
