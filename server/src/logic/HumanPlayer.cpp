#include "logic/HumanPlayer.h"

namespace logic {

    HumanPlayer::HumanPlayer(bool playing, const int fd, uint16_t colourId)
        : AbstractPlayer(playing, fd, colourId) {}

    void HumanPlayer::setMove(structure::Move move) {

    }
}