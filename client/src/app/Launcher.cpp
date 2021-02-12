#include "app/Launcher.h"
#include "communication/CommException.h"

wxIMPLEMENT_APP(Launcher);

bool Launcher::OnInit() {
    try {
        m_connector.connect();
    }
    catch (comm::CommException& ex) {
        std::cout << ex.what();
    }
    std::cout << "hey\n";

    comm::Message newMsg("Good morning");
    newMsg.addField("someInt", 99);
    newMsg.addField("someString", "Hej, ty!");
    newMsg.addField("someOtherInt", -894);
    std::cout << "hey\n";

    m_connector.send(newMsg);
    m_mainMenu = new chessGUI::MainMenu();
    m_mainMenu->Show();
    m_chessFrame = new chessGUI::ChessFrame();
    m_chessFrame->Show();
    m_mainMenu->getOption();
    return wxAppConsoleBase::OnInit();
}
