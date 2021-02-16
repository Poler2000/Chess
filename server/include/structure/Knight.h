#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

namespace structure {
    class Knight : public Figure {
    public:
        Knight(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
            m_movement = std::make_shared<Movement>(Movement{
                    false,
                    false,
                    false,
                    false,
                    true,
                    false
            });
        }

        [[nodiscard]] std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<int> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return (abs(f->getX() - this->getX()) == 2 &&
                       abs(f->getY() - this->getY()) == 1) ||
                        (abs(f->getX() - this->getX()) == 1 &&
                         abs(f->getY() - this->getY()) == 2);
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f){
                possibleFields.push_back(f->getId());
            });
            return possibleFields;
        }
    };
}

#endif //CHESS_KNIGHT_H
