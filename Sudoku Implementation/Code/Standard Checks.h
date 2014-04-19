#pragma once

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
}