//
// Created by poler on 2/11/21.
//

#include "structure/PieceFactory.h"
#include "structure/Queen.h"

namespace structure {
    std::vector<std::shared_ptr<Piece>> PieceFactory::getRed() {
        std::vector<std::shared_ptr<Piece>> pieces;
        pieces.emplace_back(std::make_shared<Piece>(Queen(2,3)));
        return pieces;
    }

    std::vector<std::shared_ptr<Piece>> PieceFactory::getBlue() {
        std::vector<std::shared_ptr<Piece>> pieces;

        return pieces;
    }
}

