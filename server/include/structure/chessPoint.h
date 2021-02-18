#ifndef CHESS_CHESSPOINT_H
#define CHESS_CHESSPOINT_H

namespace structure {
    struct chessPoint {
        int x;
        int y;

        template <class Archive>
        void serialize(Archive& ar) {
            ar(x, y);
        }
    };
}

#endif //CHESS_CHESSPOINT_H
