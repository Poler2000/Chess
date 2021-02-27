#include "gtest/gtest.h"
#include "structure/Pieces.h"

TEST (FigureTest, pieceEmptyBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
        }
    }

    structure::Figure* k = new structure::Piece(5, 6, structure::PieceFactory::getRedId());
    auto res = k->getPossibleMovements(fields);
    ASSERT_TRUE(!res.empty());
    ASSERT_EQ(res.size(), 1);
}

TEST (FigureTest, pieceFullBoard) {
    std::vector<std::shared_ptr<structure::Field>> fields;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            fields.emplace_back(std::make_shared<structure::Field>(x, y));
            if (x == 4) {
                fields.back()->setOccupied(structure::PieceFactory::getBlueId());
            }
            else if (x == 6 && y < 7) {
                fields.back()->setOccupied(structure::PieceFactory::getRedId());
            }
        }
    }

    structure::Figure* pBlue = new structure::Piece(5, 6, structure::PieceFactory::getBlueId());
    auto resBlue = pBlue->getPossibleMovements(fields);
    ASSERT_TRUE(!resBlue.empty());
    ASSERT_EQ(resBlue.size(), 2);
    structure::Figure* pRed = new structure::Piece(5, 6, structure::PieceFactory::getRedId());
    auto resRed = pRed->getPossibleMovements(fields);
    ASSERT_TRUE(!resRed.empty());
    ASSERT_EQ(resRed.size(), 2);
}