#include "gtest/gtest.h"
#include "structure/Pieces.h"

TEST (FigureTest, kingEmptyBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
        }
    }
    structure::Figure* k = new structure::King(5, 6, structure::PieceFactory::getRedId());
    auto res = k->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 8);
}

TEST (FigureTest, kingFullBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
            if (y == 5) {
                fields.back()->setOccupied(structure::PieceFactory::getRedId());
            }
            else if (y == 7 && x < 6) {
                fields.back()->setOccupied(structure::PieceFactory::getBlueId());
            }
        }

    }

    structure::Figure* k = new structure::King(5, 6, structure::PieceFactory::getBlueId());
    auto res = k->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 6);
}