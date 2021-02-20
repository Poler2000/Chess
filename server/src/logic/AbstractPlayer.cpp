#include "logic/AbstractPlayer.h"

namespace logic {

    AbstractPlayer::AbstractPlayer(const bool playing, const int fd, uint16_t colourId)
        : m_playing(playing), m_fd(fd), m_colourId(colourId) {}

    bool AbstractPlayer::isPlaying() const {
        return m_playing;
    }

    std::vector<std::shared_ptr<structure::Figure>> AbstractPlayer::getFigures() const {
        return m_figureSet;
    }

    uint16_t AbstractPlayer::getColour() const {
        return m_colourId;
    }

    structure::Move AbstractPlayer::getMove() const {
        return structure::Move();
    }

    int AbstractPlayer::getFd() const {
        return m_fd;
    }

    void AbstractPlayer::setFigures(std::vector<std::shared_ptr<structure::Figure>> figures) {
        m_figureSet = std::move(figures);
    }
}
