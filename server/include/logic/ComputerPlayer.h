#ifndef CHESS_COMPUTERPLAYER_H
#define CHESS_COMPUTERPLAYER_H

#include "AbstractPlayer.h"

namespace logic {
    class ComputerPlayer : public AbstractPlayer {
    public:
        ComputerPlayer(uint16_t i);

        void setMove(structure::Move move) override;

        structure::Move getMove() override;
    };
}

#endif //CHESS_COMPUTERPLAYER_H
