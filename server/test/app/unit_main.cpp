#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Let's start!\n";
    return RUN_ALL_TESTS();
}