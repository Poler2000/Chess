cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_executable(server app/main.cpp src/communication/CommunicationCentre.cpp include/communication/CommunicationCentre.h src/logic/GameManager.cpp include/logic/GameManager.h src/logic/Game.cpp include/logic/Game.h)