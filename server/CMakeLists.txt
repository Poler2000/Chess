cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_executable(server app/main.cpp src/communication/CommunicationCentre.cpp include/communication/CommunicationCentre.h src/logic/GameManager.cpp include/logic/GameManager.h src/logic/Game.cpp include/logic/Game.h src/structure/Field.cpp include/structure/Field.h src/communication/ClientConnector.cpp include/communication/ClientConnector.h include/communication/CommException.h src/communication/Message.cpp include/communication/Message.h src/structure/Piece.cpp include/structure/Piece.h include/structure/Movement.h src/structure/PieceFactory.cpp include/structure/PieceFactory.h include/structure/Queen.h)