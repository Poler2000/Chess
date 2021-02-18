#ifndef CHESS_ABSTRACTPLAYER_H
#define CHESS_ABSTRACTPLAYER_H

#include <vector>
#include <memory>
#include "structure/Figure.h"

namespace logic {
    class AbstractPlayer {
    public:
        bool isPlaying() const;
        std::vector<std::shared_ptr<structure::Figure>> getFigures() const;
        uint16_t getColour() const;
    protected:
        std::vector<std::shared_ptr<structure::Figure>> m_figureSet;
        uint16_t m_colourId;
        bool playing;
    private:
    };
}

#endif //CHESS_ABSTRACTPLAYER_H
