#ifndef CHESS_FIGUREDATA_H
#define CHESS_FIGUREDATA_H

#include <string>
#include <memory>
#include <cereal/types/string.hpp>

namespace structure {
    struct FigureData {
        FigureData() {}

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
