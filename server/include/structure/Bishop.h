#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

namespace structure {
    class Bishop : public Figure {
    public:
        Bishop(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    false,
                    false,
                    false,
                    true,
                    false,
                    true
            });
        }

        [[nodiscard]] std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<int> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return abs(f->getX() - this->getX()) ==
                       abs(f->getY() - this->getY());
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f) {
                possibleFields.push_back(f->getId());
            });
            return possibleFields;
        }
    };
}

#endif //CHESS_BISHOP_H
