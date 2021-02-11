#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

namespace structure {
    class Knight : public Figure {
    public:
        Knight(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    false,
                    false,
                    false,
                    false,
                    true,
                    false
            });
        }
    };
}

#endif //CHESS_KNIGHT_H
