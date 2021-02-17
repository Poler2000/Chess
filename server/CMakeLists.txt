cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)
find_package(GTest CONFIG REQUIRED)
include_directories(include)
enable_testing()

add_library(ServerEx-static STATIC app/main.cpp src/communication/CommunicationCentre.cpp include/communication/CommunicationCentre.h src/logic/GameManager.cpp include/logic/GameManager.h src/logic/Game.cpp include/logic/Game.h src/structure/Field.cpp include/structure/Field.h src/communication/ClientConnector.cpp include/communication/ClientConnector.h include/communication/CommException.h include/communication/Message.h src/structure/Figure.cpp include/structure/Figure.h include/structure/Movement.h src/structure/PieceFactory.cpp include/structure/PieceFactory.h include/structure/Queen.h include/structure/King.h include/structure/Bishop.h include/structure/Knight.h include/structure/Rook.h include/structure/Piece.h include/structure/Pieces.h include/communication/ServerConnector.h src/communication/ServerConnector.cpp src/logic/MoveValidator.cpp include/logic/MoveValidator.h test/structure/FieldTest.cpp)
add_executable(server app/main.cpp src/communication/CommunicationCentre.cpp include/communication/CommunicationCentre.h src/logic/GameManager.cpp include/logic/GameManager.h src/logic/Game.cpp include/logic/Game.h src/structure/Field.cpp include/structure/Field.h src/communication/ClientConnector.cpp include/communication/ClientConnector.h include/communication/CommException.h include/communication/Message.h src/structure/Figure.cpp include/structure/Figure.h include/structure/Movement.h src/structure/PieceFactory.cpp include/structure/PieceFactory.h include/structure/Queen.h include/structure/King.h include/structure/Bishop.h include/structure/Knight.h include/structure/Rook.h include/structure/Piece.h include/structure/Pieces.h include/communication/ServerConnector.h src/communication/ServerConnector.cpp src/logic/MoveValidator.cpp include/logic/MoveValidator.h test/structure/FieldTest.cpp)
