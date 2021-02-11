#ifndef CHESS_PIECEFACTORY_H
#define CHESS_PIECEFACTORY_H

#include <memory>
#include <vector>
#include "Figure.h"

namespace structure {
    class PieceFactory {
    public:
        static std::vector<std::shared_ptr<Figure>> getRed();
        static std::vector<std::shared_ptr<Figure>> getBlue();
    private:
        constexpr static uint16_t s_redId = 0;
        constexpr static uint16_t s_blueId = 7;
        static std::vector<std::shared_ptr<Figure>> constructPieces(uint16_t colour);
    };
}



#endif //CHESS_PIECEFACTORY_H
