#include "app/Launcher.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

wxIMPLEMENT_APP(Launcher);

bool Launcher::OnInit() {
    m_chessFrame = new chessGUI::ChessFrame();
    m_chessFrame->Show();

    m_connector.connect();
    std::string msg("Hello... it's me...");
    m_connector.send(msg);
    return wxAppConsoleBase::OnInit();
}
