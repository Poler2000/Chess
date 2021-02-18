cmake_minimum_required(VERSION 3.17)
project(Chess)

set(CMAKE_CXX_STANDARD 20)
include_directories(../include)

add_executable(ServerEx-test structure/FieldTest.cpp app/unit_main.cpp structure/RookTest.cpp structure/KnightTest.cpp structure/BishopTest.cpp structure/PieceTest.cpp structure/QueenTest.cpp structure/KingTest.cpp)
add_test(NAME ServerEx-test COMMAND ServerEx-test)

target_link_libraries(ServerEx-test PUBLIC ServerEx-static gtest gmock)


