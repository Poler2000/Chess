#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

namespace structure {
    class Piece: public Figure {
    public:
        Piece(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    true,
                    false,
                    false,
                    false,
                    false,
                    false
            });
        }
    };
}

#endif //CHESS_PIECE_H
