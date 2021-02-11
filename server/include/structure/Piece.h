#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <cstdint>
#include "Movement.h"
#include <mutex>

namespace structure {
    class Piece {
    protected:
        Piece(unsigned int x, unsigned int y, const int colour);
    public:
        Piece() = delete;
        Movement m_movement;
        void move(unsigned int x, unsigned int y);
        unsigned int getX() const;
        unsigned int getY() const;
        unsigned int getId() const;
        unsigned int getColour() const;
        Movement getPossibleMovement() const;
    private:
        unsigned int m_x;
        unsigned int m_y;
        const unsigned int m_colour;
        const uint32_t m_id;
        static std::mutex s_mtx;
        static uint32_t generateId();
    };
}

#endif //CHESS_PIECE_H
