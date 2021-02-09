#ifndef CHESS_LAUNCHER_H
#define CHESS_LAUNCHER_H

#include "chessGUI/ChessFrame.h"
#include "communication/Connector.h"

class Launcher : public wxApp {
public:
    virtual bool OnInit();

private:
    constexpr static unsigned int s_defaultPort = 8080;
    chessGUI::ChessFrame* m_chessFrame;
    comm::Connector m_connector = comm::Connector(s_defaultPort);
};

#endif //CHESS_LAUNCHER_H
