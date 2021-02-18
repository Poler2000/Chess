#include "gtest/gtest.h"
#include "structure/Pieces.h"

TEST (FigureTest, knightEmptyBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
        }
    }
    structure::Figure* k = new structure::Knight(5, 6, structure::PieceFactory::getRedId());
    auto res = k->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 6);
}

TEST (FigureTest, knightFullBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
            if (y == 4) {
                if (x == 4) {
                    fields.back()->setOccupied(structure::PieceFactory::getBlueId());
                }
                else {
                    fields.back()->setOccupied(structure::PieceFactory::getRedId());
                }
            }
        }

    }

    structure::Figure* k = new structure::Knight(5, 6, structure::PieceFactory::getBlueId());
    auto res = k->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 5);
}