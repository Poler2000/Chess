#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>

namespace structure {
    class Piece: public Figure {
    public:
        Piece(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {}

        [[nodiscard]] std::vector<ChessPoint> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<ChessPoint> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return m_colourId == PieceFactory::getRedId() ?
                       ((f->getX() == getX()) || (abs(f->getX() - (int)getX()) < 2 &&
                       f->isOccupiedBy() == PieceFactory::getBlueId())) && f->getY() - 1 == getY() :
                       ((f->getX() == getX()) || (abs(f->getX() - (int)getX()) < 2 &&
                       f->isOccupiedBy() == PieceFactory::getRedId())) && f->getY() + 1 == getY();
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f){
                if (f->isOccupiedBy() != m_colourId) {
                    possibleFields.push_back(ChessPoint{f->getX(), f->getY()});
                }
            });
            return possibleFields;
        }

        [[nodiscard]] std::string getType() const override {
            return std::string("Piece");
        }
    };
}

#endif //CHESS_PIECE_H
