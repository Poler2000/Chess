#include <communication/Message.h>
#include "../../include/logic/Game.h"

namespace logic {
    constexpr uint64_t mix(char m, uint64_t s) {
        return ((s<<7) + ~(s>>3)) + ~m;
    }

    constexpr uint64_t hash(const char * m) {
        return (*m) ? mix(*m,hash(m+1)) : 0;
    }

    /*const unsigned*/ int logic::Game::getId() const {
        return 0;
    }

    int Game::getPort() {
        return 0;
    }

    bool Game::canAddClient() {
        return false;
    }

    void Game::processMessage(const comm::Message& msg, const int clientFd) {
        switch(hash(msg.getType().c_str())) {
            case hash("StartGameMsg"):
               /* if(state != GameStates.ONE_PLAYER_READY) {
                    startGame();
                }*/
                break;
            case hash("PieceSelectedMsg"):
                break;
            case hash("MoveMsg"):
                break;
            default:
                std::cout << "Incorrect message type\n";
                break;
        }
        std::cout << "Received\n";
    }

    void Game::init() {

    }
}

