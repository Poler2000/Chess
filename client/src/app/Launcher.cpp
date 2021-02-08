#include "app/Launcher.h"

wxIMPLEMENT_APP(Launcher);

bool Launcher::OnInit() {
    m_chessFrame = new chessGUI::ChessFrame();
    m_chessFrame->Show();
    return wxAppConsoleBase::OnInit();
}
