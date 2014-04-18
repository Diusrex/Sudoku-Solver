#include "Board Data.h"

#include "Standard Checks.h"

bool BoardInformation::IsSolved(const BoardData& board)
{
    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            if (!board.board[x][y])
                return false;
        }
    }

    return true;
}