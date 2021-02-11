#include "structure/Piece.h"

namespace structure {
    structure::Piece::Piece(unsigned int x, unsigned int y, const int colour)
            : m_x(x), m_y(y), m_colour(colour), m_id(generateId()), m_movement({}) {

    }

    uint32_t Piece::generateId() {
        static uint32_t counter = 0;
        s_mtx.lock();
        uint32_t result = counter;
        counter++;
        s_mtx.unlock();
        return result;
    }
}

