#include "structure/PieceFactory.h"
#include "structure/Pieces.h"

namespace structure {
    std::vector<std::shared_ptr<Figure>> PieceFactory::getRed() {
        return constructPieces(s_redId);
    }

    std::vector<std::shared_ptr<Figure>> PieceFactory::getBlue() {
        return constructPieces(s_blueId);
    }

    std::vector<std::shared_ptr<Figure>> PieceFactory::constructPieces(uint16_t colour) {
        std::vector<std::shared_ptr<Figure>> pieces;
        int y = colour == s_redId ? colour - 1 : colour;
        pieces.emplace_back(std::make_shared<Queen>(3, y, colour));
        pieces.emplace_back(std::make_shared<King>(4, y, colour));
        pieces.emplace_back(std::make_shared<Bishop>(2, y, colour));
        pieces.emplace_back(std::make_shared<Bishop>(5, y, colour));
        pieces.emplace_back(std::make_shared<Knight>(1, y, colour));
        pieces.emplace_back(std::make_shared<Knight>(6, y, colour));
        pieces.emplace_back(std::make_shared<Rook>(0, y, colour));
        pieces.emplace_back(std::make_shared<Rook>(7, y, colour));

        for(int i = 0; i < 8; i++) {
            pieces.emplace_back(std::make_shared<Piece>(i, colour == s_redId ? 1 : 6, colour));
        }

        return pieces;
    }

    uint16_t PieceFactory::getRedId() {
        return s_redId;
    }

    uint16_t PieceFactory::getBlueId() {
        return s_blueId;
    }
}

