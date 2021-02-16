#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

#include <cstdint>
#include "Movement.h"
#include "structure/Field.h"
#include <mutex>
#include <memory>
#include <vector>
#include <ranges>

namespace structure {
    class Figure {
    protected:
        Figure(unsigned int x, unsigned int y, uint16_t colour);
        std::shared_ptr<Movement> m_movement;
        const uint16_t m_colourId;

    public:
        Figure() = delete;
        [[nodiscard]] unsigned int getX() const;
        [[nodiscard]] unsigned int getY() const;
        [[nodiscard]] unsigned int getId() const;
        [[nodiscard]] unsigned int getColour() const;
        [[nodiscard]] virtual std::vector<int> getPossibleMovements(std::vector<std::shared_ptr<structure::Field>> fields) const = 0;

        void move(unsigned int x, unsigned int y);
    private:
        uint16_t m_x;
        uint16_t m_y;
        const uint32_t m_id;
        inline static std::mutex s_mtx;

        static uint32_t generateId();
    };
}

#endif //CHESS_FIGURE_H
