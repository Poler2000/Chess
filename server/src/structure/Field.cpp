#include "structure/Field.h"

namespace structure {

    Field::Field(const unsigned int x, const unsigned int y)
        : m_xPos(x), m_yPos(y), m_id(generateId()), m_occupied(0) {}

    int Field::getX() {
        return m_xPos;
    }

    int Field::getY() {
        return m_yPos;
    }

    uint16_t Field::isOccupiedBy() {
        return m_occupied;
    }

    void Field::setOccupied(const uint16_t occupied) {
        m_occupied = occupied;
    }

    uint32_t Field::generateId() {
        static uint32_t counter = 0;
        s_mtx.lock();
        uint32_t result = counter;
        counter++;
        s_mtx.unlock();
        return result;
    }

    int Field::getId() const {
        return m_id;
    }
}