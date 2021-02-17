#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

namespace structure {
    class Knight : public Figure {
    public:
        Knight(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {}

        [[nodiscard]] std::vector<chessPoint> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<chessPoint> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return (abs(f->getX() - this->getX()) == 2 &&
                       abs(f->getY() - this->getY()) == 1) ||
                        (abs(f->getX() - this->getX()) == 1 &&
                         abs(f->getY() - this->getY()) == 2);
            });
            std::for_each(matching.begin(), matching.end(), [&](auto& f) {
                if (f->isOccupiedBy() != m_colourId) {
                    possibleFields.push_back(chessPoint{f->getX(), f->getY()});
                }
            });
            return possibleFields;
        }
    };
}

#endif //CHESS_KNIGHT_H
