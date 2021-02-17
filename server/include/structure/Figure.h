#ifndef CHESS_FIGURE_H
#define CHESS_FIGURE_H

#include <cstdint>
#include "structure/Field.h"
#include "chessPoint.h"
#include <mutex>
#include <memory>
#include <vector>
#include <ranges>
#include <algorithm>

namespace structure {
    class Figure {
    protected:
        Figure(unsigned int x, unsigned int y, uint16_t colour);
        const uint16_t m_colourId;

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getNorth(auto fields) const {
            auto vertical = fields | std::views::filter([&](auto& f) {
                return f->getX() == getX() &&
                        f->getY() < getY();
            });
            auto verVec = std::vector(std::ranges::begin(vertical), std::ranges::end(vertical));
            std::ranges::sort(verVec.begin(), verVec.end(), [](auto& f, auto& g) {
                return f->getY() > g->getY();
            });
            return verVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getSouth(auto fields) const {
            auto vertical = fields | std::views::filter([&](auto& f) {
                return f->getX() == getX() &&
                       f->getY() > getY();
            });
            auto verVec = std::vector(std::ranges::begin(vertical), std::ranges::end(vertical));
            std::ranges::sort(verVec.begin(), verVec.end(), [](auto& f, auto& g) {
                return f->getY() < g->getY();
            });
            return verVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getWest(auto fields) const {
            auto horizontal = fields | std::views::filter([&](auto& f) {
                return f->getY() == getY() &&
                       f->getX() < getX();
            });
            auto horVec = std::vector(std::ranges::begin(horizontal), std::ranges::end(horizontal));
            std::ranges::sort(horVec.begin(), horVec.end(), [](auto& f, auto& g) {
                return f->getX() > g->getX();
            });
            return horVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getEast(auto fields) const {
            auto horizontal = fields | std::views::filter([&](auto& f) {
                return f->getY() == getY() &&
                       f->getX() > getX();
            });
            auto horVec = std::vector(std::ranges::begin(horizontal), std::ranges::end(horizontal));
            std::ranges::sort(horVec.begin(), horVec.end(), [](auto& f, auto& g) {
                return f->getX() < g->getX();
            });
            return horVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getNorthWest(auto fields) const {
            auto diagonal = fields | std::views::filter([&](auto& f) {
                return ((int)getY() - (int)f->getY()) > 0 &&
                        ((int)getX() - (int)f->getX()) > 0;
            });
            auto diagVec = std::vector(std::ranges::begin(diagonal), std::ranges::end(diagonal));
            std::ranges::sort(diagVec.begin(), diagVec.end(), [](auto& f, auto& g) {
                return f->getX() > g->getX();
            });
            return diagVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getNorthEast(auto fields) const {
            auto diagonal = fields | std::views::filter([&](auto& f) {
                return ((int)getY() - (int)f->getY()) > 0 &&
                       ((int)getX() - (int)f->getX()) < 0;
            });
            auto diagVec = std::vector(std::ranges::begin(diagonal), std::ranges::end(diagonal));
            std::ranges::sort(diagVec.begin(), diagVec.end(), [](auto& f, auto& g) {
                return f->getX() < g->getX();
            });
            return diagVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getSouthWest(auto fields) const {
            auto diagonal = fields | std::views::filter([&](auto& f) {
                return ((int)getY() - (int)f->getY()) < 0 &&
                       ((int)getX() - (int)f->getX()) > 0;
            });
            auto diagVec = std::vector(std::ranges::begin(diagonal), std::ranges::end(diagonal));
            std::ranges::sort(diagVec.begin(), diagVec.end(), [](auto& f, auto& g) {
                return f->getX() > g->getX();
            });
            return diagVec;
        };

        [[nodiscard]] std::vector<std::shared_ptr<Field>> getSouthEast(auto fields) const {
            auto diagonal = fields | std::views::filter([&](auto& f) {
                return ((int)getY() - (int)f->getY()) < 0 &&
                       ((int)getX() - (int)f->getX()) < 0;
            });
            auto diagVec = std::vector(std::ranges::begin(diagonal), std::ranges::end(diagonal));
            std::ranges::sort(diagVec.begin(), diagVec.end(), [](auto& f, auto& g) {
                return f->getX() < g->getX();
            });
            return diagVec;
        };

    public:
        Figure() = delete;
        [[nodiscard]] unsigned int getX() const;
        [[nodiscard]] unsigned int getY() const;
        [[nodiscard]] unsigned int getId() const;
        [[nodiscard]] unsigned int getColour() const;
        [[nodiscard]] virtual std::vector<chessPoint> getPossibleMovements(std::vector<std::shared_ptr<Field>> fields) const = 0;

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
