// Copyright © Mattias Larsson Sköld 2020

#include "board.h"

#include <iostream>
#include <random>

using namespace std;

int main(int /*argc*/, char ** /*argv*/) {
    cout << "Hello" << endl;

    auto width = 10u, height = 10u;

    random_device dev;
    default_random_engine eng;
    uniform_int_distribution<size_t> wdist(0, width - 1);
    uniform_int_distribution<size_t> hdist(0, height - 1);
    Board board(width, height);

    for (int i = 0; i < 3; ++i) {
        size_t x = wdist(dev);
        size_t y = hdist(dev);

        board.addQueen(x, y);
    }

    cout << board << endl;

    cout << board.numThreatenedQueens() << endl;

    return 0;
}
