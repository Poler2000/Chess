#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

namespace structure {
    class Queen : public Piece {
    public:
        Queen(const unsigned int x, const unsigned int y, const int colour) : Piece(x, y, colour) {
            m_movement.up = true;
        }

    };
}



#endif //CHESS_QUEEN_H
