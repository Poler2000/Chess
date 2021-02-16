#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

namespace structure {
    class Rook : public Figure {
    public:
        Rook(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {
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
                    f->getY() == getY();
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

#endif //CHESS_ROOK_H
