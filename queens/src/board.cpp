// Copyright © Mattias Larsson Sköld 2020
#include "board.h"
#include <iostream>

namespace {

// Check if queen and position is on the same diagonal
bool queenCheck(size_t x, size_t y, Board::Coord c) {
    int dx = static_cast<int>(x - c.x);
    int dy = static_cast<int>(y - c.y);

    return (abs(dx) == abs(dy));
}

} // namespace

Board::Board(size_t width, size_t height)
    : _data(width * height), _width(width), _height(height) {
}

bool Board::isThreatenedByQueen(size_t x, size_t y) const {
    for (auto q : _queens) {
        if (queenCheck(x, y, q)) {
            return true;
        }
    }
    return false;
}

size_t Board::numThreatenedQueens() const {
    size_t sum = 0;
    for (auto q : _queens) {
        if (isThreatenedByQueen(q.x, q.y)) {
            ++sum;
        }
    }
    return sum;
}

std::ostream &operator<<(std::ostream &stream, const Board &board) {
    for (size_t y = 0; y < board.height(); ++y) {
        for (size_t x = 0; x < board.width(); ++x) {
            stream << " ";
            if (board(x, y)) {
                stream << "♕";
            }
            else if (board.isThreatenedByQueen(x, y)) {
                stream << "x";
            }
            else {
                stream << ".";
            }
            stream << " ";
        }
        stream << "\n";
    }
    return stream;
}
