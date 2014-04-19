#pragma once

#include <vector>

namespace BoardInformation
{
    struct BoardData;
}


class Algorithm {
public:
    // Returns true if the board was valid, otherwise returns true.
        // Note: the puzzle should not have had SetUpPossibleSpots been called on it yet
    bool BeginSolving(BoardInformation::BoardData & board);

protected:
    virtual void Solve(BoardInformation::BoardData & board) = 0;

    void GuessSpot(BoardInformation::BoardData & board);

};