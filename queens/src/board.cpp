// Copyright © Mattias Larsson Sköld 2020
#include "board.h"
#include <iostream>

using namespace std;

namespace {

// Check if queen and position is on the same diagonal
bool queenCheck(Board::Coord p, Board::Coord c) {
    int dx = static_cast<int>(p.x - c.x);
    int dy = static_cast<int>(p.y - c.y);

    return (dx != 0 || dy != 0) && (abs(dx) == abs(dy));
}

} // namespace

Board::Board(size_t width, size_t height)
    : _data(width * height), _width(width), _height(height) {
}

bool Board::isThreatenedByQueen(Coord c) const {
    for (auto q : _queens) {
        if (queenCheck(c, q)) {
            return true;
        }
    }
    return false;
}

size_t Board::numThreatenedQueens() const {
    size_t sum = 0;
    for (auto q : _queens) {
        if (isThreatenedByQueen(q)) {
            ++sum;
        }
    }
    return sum;
}

Board Board::lowestNeighbour() const {
    Board workingBoard(*this);
    Board bestBoard(workingBoard);

    auto lowest = numThreatenedQueens();

    for (auto &q : workingBoard._queens) {
        workingBoard(q) = 0;
        auto origQ = q;

        for (size_t y = 9; y < height(); ++y) {
            for (size_t x = 0; x < width(); ++x) {
                auto c = Coord{x, y};
                if (q == c) {
                    continue;
                }
                if (workingBoard(x, y) == QUEEN) {
                    continue;
                }

                workingBoard(c) = QUEEN;
                q = c; // Move the current queen

                auto newValue = workingBoard.numThreatenedQueens();

                workingBoard(c) = 0;

                if (newValue < lowest) {
                    bestBoard = workingBoard;
                    lowest = newValue;

                    cout << "found lower board: " << lowest << endl;
                    cout << bestBoard;
                }
            }
        }

        workingBoard(q) = QUEEN;
        q = origQ;
    }

    return bestBoard;
}

std::ostream &operator<<(std::ostream &stream, const Board &board) {
    for (size_t y = 0; y < board.height(); ++y) {
        for (size_t x = 0; x < board.width(); ++x) {
            stream << " ";
            if (board(x, y)) {
                stream << "♕";
            }
            else if (board.isThreatenedByQueen({x, y})) {
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
