#ifndef CHESS_ABSTRACTPLAYER_H
#define CHESS_ABSTRACTPLAYER_H

#include <vector>
#include <memory>
#include "structure/Figure.h"
#include "structure/Move.h"

namespace logic {
    class AbstractPlayer {
    public:
        [[nodiscard]] bool isPlaying() const;
        [[nodiscard]] std::vector<std::shared_ptr<structure::Figure>> getFigures() const;
        [[nodiscard]] uint16_t getColour() const;
        [[nodiscard]] structure::Move getMove() const;
        int getFd() const;
    protected:
        std::vector<std::shared_ptr<structure::Figure>> m_figureSet;
        uint16_t m_colourId;
        bool playing;
    private:
    };
}

#endif //CHESS_ABSTRACTPLAYER_H
