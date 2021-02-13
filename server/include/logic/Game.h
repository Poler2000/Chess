#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <vector>
#include "communication/Message.h"

namespace logic {
    class Game {
    public:
        /*const unsigned*/ int getId() const;

        int getPort();
        void init();
        bool canAddClient();

        void processMessage(const comm::Message &msg, const int clientFd);
    };
}



#endif //CHESS_GAME_H
