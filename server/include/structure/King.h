#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <list>
#include <cmath>

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

        [[nodiscard]] std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<int> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return abs(f->getX() - this->getX()) < 2 &&
                        abs(f->getY() - this->getY()) < 2;
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f) {
                if (f->isOccupiedBy() != m_colourId) {
                    possibleFields.push_back(f->getId());
                }
            });
            return possibleFields;
        }
    };
}

#endif //CHESS_KING_H
