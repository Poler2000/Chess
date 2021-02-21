#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H

#include "AbstractPlayer.h"

namespace logic {
    class HumanPlayer : public AbstractPlayer {
    public:
        HumanPlayer(bool playing, const int fd, uint16_t colourId);

        void setMove(structure::Move move) override;
    };
}

#endif //CHESS_HUMANPLAYER_H
