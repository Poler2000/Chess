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

        [[nodiscard]] std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<int> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return m_colourId == PieceFactory::getRedId() ?
                f->getX() == getX() && f->getY() + 1 == getY() :
                f->getX() == getX() && f->getY() - 1 == getY();
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f){
                possibleFields.push_back(f->getId());
            });
            return possibleFields;
        }
    };
}

#endif //CHESS_PIECE_H
