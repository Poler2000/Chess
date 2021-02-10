cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include)
add_executable(client src/app/Launcher.cpp include/app/Launcher.h src/chessGUI/ChessFrame.cpp include/chessGUI/ChessFrame.h include/communication/Connector.h src/communication/Connector.cpp include/communication/CommException.h src/chessGUI/ChessField.cpp include/chessGUI/ChessField.h)
target_link_libraries(client ${wxWidgets_LIBRARIES})
