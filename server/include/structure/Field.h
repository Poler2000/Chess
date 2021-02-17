#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

#include <cstdint>
#include <mutex>

namespace structure {
    class Field {
    public:
        Field(unsigned int x, unsigned int y);
        int getX();
        int getY();
        uint16_t isOccupiedBy();
        void setOccupied(uint16_t empty);
        [[nodiscard]] int getId() const;
    private:
        const unsigned int m_xPos;
        const unsigned int m_yPos;
        uint16_t m_occupied;
        const uint32_t m_id;
        inline static std::mutex s_mtx;

        static uint32_t generateId();
    };
}

#endif //CHESS_FIELD_H
