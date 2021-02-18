#include "gtest/gtest.h"
#include "structure/Pieces.h"

TEST (FigureTest, queenEmptyBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
        }
    }
    structure::Figure* q = new structure::Queen(5, 6, structure::PieceFactory::getRedId());
    auto res = q->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 23);
}

TEST (FigureTest, queenFullBoard) {
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

    structure::Figure* q = new structure::Queen(5, 6, structure::PieceFactory::getBlueId());
    auto res = q->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 15);
}