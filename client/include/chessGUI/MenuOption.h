#ifndef CHESS_MENUOPTION_H
#define CHESS_MENUOPTION_H
namespace chessGUI {
    struct MenuOption {
        int optionId;
        int itemId;
    };

    enum MenuOptionValues{
        NONE,
        CREATE,
        JOIN,
        WATCH,
        REPLAY
    };
}


#endif //CHESS_MENUOPTION_H
