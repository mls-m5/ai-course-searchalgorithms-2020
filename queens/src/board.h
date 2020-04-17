// Copyright © Mattias Larsson Sköld 2020

#pragma once

#include <iosfwd>
#include <vector>

class Board {
public:
    struct Coord {
        size_t x = 0;
        size_t y = 0;
    };

    Board(size_t width, size_t height);

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

    bool isThreatenedByQueen(size_t x, size_t y) const;

    size_t numThreatenedQueens() const;

private:
    int &operator()(size_t x, size_t y) {
        return _data.at(x + y * _width);
    }

    std::vector<int> _data;
    std::vector<Coord> _queens;
    size_t _width;
    size_t _height;
};

std::ostream &operator<<(std::ostream &stream, const Board &board);
