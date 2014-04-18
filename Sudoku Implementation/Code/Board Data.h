#pragma once

#include <vector>

struct BoardData {

    void SetUp(size_t boxSize);
    std::vector<std::vector<int>> board;

    // boardSize is also the highest number that can be placed
    size_t boardSize, boxSize;

    // Will nicely print out the array
    void PrintOut() const;
};