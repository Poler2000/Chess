#include "logic/AbstractPlayer.h"

namespace logic {

    bool AbstractPlayer::isPlaying() const {
        return false;
    }

    std::vector<std::shared_ptr<structure::Figure>> AbstractPlayer::getFigures() const {
        return std::vector<std::shared_ptr<structure::Figure>>();
    }

    uint16_t AbstractPlayer::getColour() const {
        return 0;
    }

    structure::Move AbstractPlayer::getMove() const {
        return structure::Move();
    }

    int AbstractPlayer::getFd() const {
        return 0;
    }
}
