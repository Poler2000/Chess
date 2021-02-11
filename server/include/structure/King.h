#ifndef CHESS_KING_H
#define CHESS_KING_H

namespace structure {
    class King : public Figure {
    public:
        King(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    true,
                    true,
                    true,
                    true,
                    false,
                    false
            });
        }
    };
}

#endif //CHESS_KING_H
