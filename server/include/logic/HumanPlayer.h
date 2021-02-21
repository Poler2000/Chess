#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H

#include "AbstractPlayer.h"
#include <mutex>

namespace logic {
    class HumanPlayer : public AbstractPlayer {
    public:
        HumanPlayer(bool playing, const int fd, uint16_t colourId);

        void setMove(structure::Move move) override;

        structure::Move getMove() override;

    private:
        std::mutex m_mtx;
    };
}

#endif //CHESS_HUMANPLAYER_H
