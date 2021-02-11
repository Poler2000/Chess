#ifndef CHESS_PIECEFACTORY_H
#define CHESS_PIECEFACTORY_H

#include <memory>
#include <vector>
#include "Piece.h"

namespace structure {
    class PieceFactory {
        static std::vector<std::shared_ptr<Piece>> getRed();
        static std::vector<std::shared_ptr<Piece>> getBlue();
    };
}



#endif //CHESS_PIECEFACTORY_H
