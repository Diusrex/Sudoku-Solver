#pragma once

#include <vector>

namespace BoardInformation {
    struct BoardData {

        void SetUpSizes(size_t boxSize);

        // [x][y]
        std::vector<std::vector<int>> board;

        // Will store if a specific position can be placed in [num][x][y]
        std::vector<std::vector<std::vector<bool>>> canBePlacedIn;

        // Will store if the number is in each box. Will be [num][sectionX][sectionY]
        std::vector<std::vector<std::vector<bool>>> numberPlacedInSection;

        // boardSize is also the highest number that can be placed
        size_t boardSize, boxSize;

        // Will nicely print out the array
        void PrintOut() const;
    };

    // Will set up canBePlacedIn and numberPlacedInBox
        // Note, should not be called when the board is changed, only when it is loaded
    bool SetUpPossibleSpots(BoardData & board);

    // Will update the vertical and horizontal availability of the given number, as well as it's availability in the section
    void UpdatePossibleSpots(BoardData & board, size_t takenNum, size_t x, size_t y);
}