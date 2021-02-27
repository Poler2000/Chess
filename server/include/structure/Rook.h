#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include <algorithm>

namespace structure {
    class Rook : public Figure {
    public:
        Rook(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {}

        [[nodiscard]] std::vector<ChessPoint> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<ChessPoint> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return f->getX() == getX() ||
                    f->getY() == getY();
            });

            std::array<std::vector<std::shared_ptr<Field>>, 4> fieldsSorted;
            fieldsSorted[0] = getNorth(matching);
            fieldsSorted[1] = getSouth(matching);
            fieldsSorted[2] = getWest(matching);
            fieldsSorted[3] = getEast(matching);

            std::for_each(fieldsSorted.begin(), fieldsSorted.end(), [&](auto vec){
                for (auto& f : vec) {
                    if (f->isOccupiedBy() != m_colourId) {
                        possibleFields.push_back(ChessPoint{f->getX(), f->getY()});
                    }
                    if (f->isOccupiedBy() != 0) {
                        break;
                    }
                }
            });

            return possibleFields;
        }

        [[nodiscard]] std::string getType() const override {
            return std::string("Rook");
        }
    };
}

#endif //CHESS_ROOK_H
