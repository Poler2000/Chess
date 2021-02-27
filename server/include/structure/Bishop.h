#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

namespace structure {
    class Bishop : public Figure {
    public:
        Bishop(const unsigned int x, const unsigned int y, const int colour) : Figure(x, y, colour) {}

        [[nodiscard]] std::vector<ChessPoint> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const override {
            std::vector<ChessPoint> possibleFields;
            auto matching = fields | std::views::filter([&](auto& f) {
                return abs((int)f->getX() - (int)this->getX()) ==
                       abs((int)f->getY() - (int)this->getY());
            });

            std::array<std::vector<std::shared_ptr<Field>>, 4> fieldsSorted;
            fieldsSorted[0] = getNorthEast(matching);
            fieldsSorted[1] = getNorthWest(matching);
            fieldsSorted[2] = getSouthEast(matching);
            fieldsSorted[3] = getSouthWest(matching);

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
            return std::string("Bishop");
        }
    };
}

#endif //CHESS_BISHOP_H
