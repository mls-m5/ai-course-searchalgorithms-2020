// Copyright © Mattias Larsson Sköld 2020

#pragma once

#include <iosfwd>
#include <vector>

#define QUEEN 'Q'

//! Notice that this is optimiced for speed of writing code and not speed of
//! running the program
class Board {
public:
    struct Coord {
        size_t x = 0;
        size_t y = 0;

        bool operator==(const Coord &c) {
            return c.x == x && c.y == y;
        }

        bool operator!=(const Coord &c) {
            return !(*this == c);
        }
    };

    Board(size_t width, size_t height);
    Board(Board &&) = default;
    Board(const Board &) = default;
    Board &operator=(Board &&) = default;
    Board &operator=(const Board &) = default;

    int operator()(size_t x, size_t y) const {
        return _data.at(x + y * _width);
    }

    void addQueen(size_t x, size_t y) {
        (*this)(x, y) = 'Q';
        _queens.push_back({x, y});
    }

    size_t height() const {
        return _height;
    }

    size_t width() const {
        return _width;
    }

    bool isThreatenedByQueen(Coord c) const;

    size_t numThreatenedQueens() const;

    //! Bets imediate change
    //! Can be used for gradient descent for example
    Board lowestNeighbour() const;

private:
    int &operator()(size_t x, size_t y) {
        return _data.at(x + y * _width);
    }

    int &operator()(Coord c) {
        return _data.at(c.x + c.y * _width);
    }

    std::vector<int> _data;
    std::vector<Coord> _queens;
    size_t _width;
    size_t _height;
};

std::ostream &operator<<(std::ostream &stream, const Board &board);
