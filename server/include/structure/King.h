#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <list>
#include <cmath>

namespace structure {
    class King : public Figure {
    public:
        King(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {}

        [[nodiscard]] std::vector<ChessPoint> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<ChessPoint> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return abs((int)f->getX() - (int)this->getX()) < 2 &&
                        abs((int)f->getY() - (int)this->getY()) < 2;
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f) {
                if (f->isOccupiedBy() != m_colourId && (f->getX() != getX() || f->getY() != getY())) {
                    possibleFields.push_back(ChessPoint{f->getX(), f->getY()});
                }
            });
            return possibleFields;
        }

        [[nodiscard]] std::string getType() const override {
            return std::string("King");
        }
    };
}

#endif //CHESS_KING_H
