#pragma once

#include <vector>

namespace BoardInformation
{
    class BoardData;
}


class Algorithm {
public:
    // Returns true if the board was valid, otherwise returns true.
        // Note: the puzzle should not have had SetUpPossibleSpots been called on it yet
    bool BeginSolving(BoardInformation::BoardData & board);

protected:
    virtual void Solve(BoardInformation::BoardData & board) = 0;

    virtual void GuessSpot(BoardInformation::BoardData & board);

};