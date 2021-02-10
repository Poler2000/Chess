#include "logic/GameManager.h"

int main(int argc, char const *argv[]) {
    logic::GameManager gameManager;
    gameManager.init();
    gameManager.run();
    return 0;
} 