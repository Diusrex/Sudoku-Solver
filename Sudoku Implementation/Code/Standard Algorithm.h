#pragma once

#include "Base Algorithm.h"

class StandardAlgorithm : public Algorithm
{
    void Solve(BoardInformation::BoardData &board) override;

    // Will go through each box, and change it's number if only one number can be placed in it
    bool CheckSingleOptions(BoardInformation::BoardData &board);
};