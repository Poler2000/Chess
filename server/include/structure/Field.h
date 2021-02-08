#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

namespace structure {
    class Field {
    public:
        Field(const unsigned int x, const unsigned int y);
        int getX();
        int getY();
        bool isEmpty();
        void setEmpty();
    private:
        const unsigned int xPos;
        const unsigned int yPos;
        bool empty;
    };
}

#endif //CHESS_FIELD_H
