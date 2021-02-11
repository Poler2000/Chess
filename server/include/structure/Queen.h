#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Figure.h"

namespace structure {
    class Queen : public Figure {
    public:
        Queen(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    true,
                    true,
                    true,
                    true,
                    false,
                    true
            });
        }
    };
}



#endif //CHESS_QUEEN_H
