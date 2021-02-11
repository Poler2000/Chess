#ifndef CHESS_MOVEMENT_H
#define CHESS_MOVEMENT_H

namespace structure {
    struct Movement {
        const bool up;
        const bool down;
        const bool side;
        const bool diagonal;
        const bool jump;
        const bool multipleFields;
    };
}

#endif //CHESS_MOVEMENT_H
