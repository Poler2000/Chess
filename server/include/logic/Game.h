#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <vector>
#include "communication/Message.h"
#include "communication/ClientConnector.h"
#include <memory>
#include <queue>

namespace comm {
   class ClientConnector;
}

namespace logic {
    class Game {
    public:
        Game();
        //Game(Game game);
        Game(Game const& game);

        int getId() const;

        int getPort();
        void init();
        bool canAddClient();

        void processMessage(const comm::Message &msg, const int clientFd);
        void addMessageToQueue(const comm::Message& msg, const int clientFd);
        void monitorMessages();
    private:
        const uint32_t m_id;
        std::shared_ptr<comm::ClientConnector> m_connector;
        std::queue<std::pair<comm::Message, const int>> m_msgQueue;

    };
}



#endif //CHESS_GAME_H
