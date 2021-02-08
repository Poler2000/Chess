#ifndef CHESS_LAUNCHER_H
#define CHESS_LAUNCHER_H

#include "chessGUI/ChessFrame.h"

class Launcher : public wxApp {
public:
    virtual bool OnInit();

private:
    chessGUI::ChessFrame* m_chessFrame;
};

#endif //CHESS_LAUNCHER_H
