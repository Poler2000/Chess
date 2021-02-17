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

        [[nodiscard]] std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<int> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return f->getX() == getX() ||
                       f->getY() == getY() ||
                        abs((int)f->getX() - (int)this->getX()) ==
                        abs((int)f->getY() - (int)this->getY());
            });

            std::array<std::vector<std::shared_ptr<Field>>, 8> fieldsSorted;
            fieldsSorted[0] = getNorth(matching);
            fieldsSorted[1] = getSouth(matching);
            fieldsSorted[2] = getWest(matching);
            fieldsSorted[3] = getEast(matching);
            fieldsSorted[4] = getNorthEast(matching);
            fieldsSorted[5] = getNorthWest(matching);
            fieldsSorted[6] = getSouthEast(matching);
            fieldsSorted[7] = getSouthWest(matching);

            std::for_each(fieldsSorted.begin(), fieldsSorted.end(), [&](auto vec){
                for (auto& f : vec) {
                    if (f->isOccupiedBy() != m_colourId) {
                        possibleFields.push_back(f->getId());
                    }
                    if (f->isOccupiedBy() != 0) {
                        break;
                    }
                }
            });

            return possibleFields;
        }
    };
}



#endif //CHESS_QUEEN_H
