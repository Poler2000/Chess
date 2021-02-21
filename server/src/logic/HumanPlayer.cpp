#include "logic/HumanPlayer.h"

namespace logic {

    HumanPlayer::HumanPlayer(bool playing, const int fd, uint16_t colourId)
        : AbstractPlayer(playing, fd, colourId) {}

    void HumanPlayer::setMove(structure::Move move) {
        m_mtx.lock();
        m_currentMove = move;
        m_mtx.unlock();
    }

    structure::Move HumanPlayer::getMove() {
        while (m_currentMove.pieceId == -1) {
            m_mtx.lock();
            m_mtx.unlock();
        }
        m_currentMove = {-1,-1,-1};
        return structure::Move();
    }
}