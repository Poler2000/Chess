#include "gtest/gtest.h"
#include "structure/Pieces.h"

TEST (FigureTest, bishopEmptyBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
        }
    }
    structure::Figure* b = new structure::Bishop(5, 6, structure::PieceFactory::getRedId());
    auto res = b->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 9);
}

TEST (FigureTest, bishopFullBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
            if (y == 2) {
                fields.back()->setOccupied(structure::PieceFactory::getRedId());
            }
            else if (y == 3) {
                fields.back()->setOccupied(structure::PieceFactory::getBlueId());
            }
            if (x == 2) {
                fields.back()->setOccupied(structure::PieceFactory::getRedId());
            }
        }

    }

    structure::Figure* b = new structure::Bishop(5, 6, structure::PieceFactory::getBlueId());
    auto res = b->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 7);
}