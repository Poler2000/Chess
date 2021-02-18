#ifndef CHESS_FIGUREDATA_H
#define CHESS_FIGUREDATA_H

#include <string>
#include <memory>
#include "Figure.h"

namespace structure {
    struct FigureData {
        FigureData(std::shared_ptr<Figure> figure)
            : id(figure->getId()), colourId(figure->getColour()), pieceType(figure->getType()),
            x(figure->getX()), y(figure->getY()) {}

        unsigned int id;
        unsigned int colourId;
        std::string pieceType;
        unsigned int x;
        unsigned int y;

        template <class Archive>
        void serialize(Archive& ar) {
            ar(id, colourId, pieceType, x, y);
        }
    };
}

#endif //CHESS_FIGUREDATA_H
