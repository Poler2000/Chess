#include "structure/Figure.h"

namespace structure {
    structure::Figure::Figure(const unsigned int x, const unsigned int y, const uint16_t colour)
            : m_x(x), m_y(y), m_colourId(colour), m_id(generateId()) {}

    uint32_t Figure::generateId() {
        static uint32_t counter = 0;
        s_mtx.lock();
        uint32_t result = counter;
        counter++;
        s_mtx.unlock();
        return result;
    }

    void Figure::move(unsigned int x, unsigned int y) {
        if (x < 8) {
            m_x = x;
        }
        if (y < 8) {
            m_y = y;
        }
    }

    unsigned int Figure::getX() const {
        return m_x;
    }

    unsigned int Figure::getY() const {
        return m_y;
    }

    unsigned int Figure::getId() const {
        return m_id;
    }

    unsigned int Figure::getColour() const {
        return m_colourId;
    }
}

