#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

namespace structure {
    class Rook : public Figure {
    public:
        Rook(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
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

#endif //CHESS_ROOK_H
