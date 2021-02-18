#ifndef CHESS_PIECEFACTORY_H
#define CHESS_PIECEFACTORY_H

#include <memory>
#include <vector>
#include "Figure.h"

namespace structure {
    class Figure;

    class PieceFactory {
    public:
        static std::vector<std::shared_ptr<Figure>> getRed();
        static std::vector<std::shared_ptr<Figure>> getBlue();
        static uint16_t getRedId();
        static uint16_t getBlueId();
    private:
        constexpr static uint16_t s_redId = 1;
        constexpr static uint16_t s_blueId = 7;
        static std::vector<std::shared_ptr<Figure>> constructPieces(uint16_t colour);
    };
}



#endif //CHESS_PIECEFACTORY_H
