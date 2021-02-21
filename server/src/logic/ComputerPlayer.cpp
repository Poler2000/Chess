#include "logic/ComputerPlayer.h"

namespace logic {

    ComputerPlayer::ComputerPlayer(const uint16_t colourId)
        : AbstractPlayer(true, 0, colourId) {}

    void ComputerPlayer::setMove(structure::Move move) {

    }

    structure::Move ComputerPlayer::getMove() {
        return structure::Move();
    }
}