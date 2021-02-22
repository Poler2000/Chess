#ifndef CHESS_ABSTRACTPLAYER_H
#define CHESS_ABSTRACTPLAYER_H

#include <vector>
#include <memory>
#include "structure/Figure.h"
#include "structure/Move.h"

namespace logic {
    class AbstractPlayer {
    public:
        AbstractPlayer(bool playing, const int i, uint16_t i1);

        [[nodiscard]] bool isPlaying() const;
        [[nodiscard]] std::vector<std::shared_ptr<structure::Figure>> getFigures() const;
        [[nodiscard]] uint16_t getColour() const;
        [[nodiscard]] virtual structure::Move getMove() = 0;
        [[nodiscard]] int getFd() const;

        void setFigures(std::vector<std::shared_ptr<structure::Figure>> figures);
        virtual void setMove(structure::Move move) = 0;
    protected:
        std::vector<std::shared_ptr<structure::Figure>> m_figureSet;
        uint16_t m_colourId;
        bool m_playing;
        int m_fd;
        structure::Move m_currentMove{-1, -1, -1};
    private:
    };
}

#endif //CHESS_ABSTRACTPLAYER_H
