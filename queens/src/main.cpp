// Copyright © Mattias Larsson Sköld 2020

#include "board.h"

#include <functional>
#include <iostream>
#include <random>

using namespace std;

Board gradientDescent(const Board board,
                      std::function<long(const Board &)> heuristic) {
    auto node = move(board);
    while (true) {
        auto nodeValue = heuristic(node);
        auto neighbour = board.lowestNeighbour();
        if (heuristic(neighbour) >= nodeValue) {
            return node;
        }
        node = neighbour;
    }
}

int main(int /*argc*/, char ** /*argv*/) {
    cout << "Hello" << endl;

    auto width = 8u, height = width;

    random_device dev;
    default_random_engine eng;
    uniform_int_distribution<size_t> hdist(0, height - 1);
    Board board(width, height);

    for (size_t i = 0; i < width; ++i) {
        size_t y = hdist(dev);

        board.addQueen(i, y);
    }

    cout << board << endl;
    cout << "Threatening queens: " << board.numThreatenedQueens() << endl;

    auto solution =
        gradientDescent(board, [](auto &b) { return b.numThreatenedQueens(); });

    cout << "Threatening queens in \" solution \": "
         << solution.numThreatenedQueens() << endl;

    return 0;
}
