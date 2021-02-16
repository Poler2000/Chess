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
                return m_colourId == 1 ?
                       f->getX() == getX() && f->getY() + 1 == getY() :
                       f->getX() == getX() && f->getY() - 1 == getY();
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f){
                if (f->isOccupiedBy() != m_colourId) {
                    possibleFields.push_back(f->getId());
                }
            });
            return possibleFields;
        }
    };
}



#endif //CHESS_QUEEN_H
