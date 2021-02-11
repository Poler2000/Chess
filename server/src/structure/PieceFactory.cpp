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

        pieces.emplace_back(std::make_shared<Figure>(Queen(3, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(King(4, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Bishop(2, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Bishop(5, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Knight(1, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Knight(6, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Rook(1, colour, colour)));
        pieces.emplace_back(std::make_shared<Figure>(Rook(7, colour, colour)));

        for(int i = 0; i < 8; i++) {
            pieces.emplace_back(std::make_shared<Figure>(Piece(i, colour == 0 ? 1 : 6, colour)));
        }

        return pieces;
    }
}

