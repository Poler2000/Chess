#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

namespace structure {
    class Bishop : public Figure {
    public:
        Bishop(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    false,
                    false,
                    false,
                    true,
                    false,
                    true
            });
        }
    };
}

#endif //CHESS_BISHOP_H
