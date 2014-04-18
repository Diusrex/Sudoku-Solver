#pragma once

#include <vector>

namespace BoardInformation {
    struct BoardData {

        void SetUp(size_t boxSize);

        // [x][y]
        std::vector<std::vector<int>> board;

        // Will store if a specific position can be placed in [num][x][y]
        std::vector<std::vector<std::vector<bool>>> canBePlacedIn;

        // Will store if the number is in each box. Will be [num][boxX][boxY]
        std::vector<std::vector<std::vector<bool>>> numberPlacedInBox;

        // boardSize is also the highest number that can be placed
        size_t boardSize, boxSize;

        // Will nicely print out the array
        void PrintOut() const;
    };
}