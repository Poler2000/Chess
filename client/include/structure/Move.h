#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

namespace structure {
    struct Move {
        int pieceId;
        int destX;
        int destY;

        template <class Archive>
        void serialize(Archive& ar) {
            ar(pieceId, destX, destY);
        }
    };
}

#endif //CHESS_MOVE_H