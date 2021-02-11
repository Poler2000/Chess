#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <vector>

namespace logic {
    class Game {
    public:
        const unsigned int getId() const;

        int getPort();

        bool canAddClient();
    };
}



#endif //CHESS_GAME_H
