#pragma once

#include <vector>

namespace BoardInformation {

    struct BoardData;

    // Will check to see if the given board is solved. 
        // Note: Will NOT check to see if the board is valid, only if all positions have a value
    bool IsSolved(const BoardData& board);

    // Will check to see if the given board is impossible. Currently only checks for box validity
        // EDIT: Implement checks for row and column impossibilities.
    bool IsImpossible(const BoardData & board);

    // Will return 0 if multiple numbers can be placed, will otherwise return a the only number that can be placed
    size_t GetOnlyNumberCanBePlaced(const BoardData & board, size_t x, size_t y);

    // The row/columnOnlyPos only will be of size board.boardSize + 1, and will store where each line may only go.
    // Does not matter what is stored in each container
    void GetRowAndColumnOnlyPossible(const BoardData & board, const size_t linePos, std::vector<int>& rowOnlyPos, std::vector<bool>& singleRowPos, std::vector<int>& columnOnlyPos, std::vector<bool>& singleColumnPos);
}