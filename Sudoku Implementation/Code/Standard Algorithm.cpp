#include "Board Data.h"
#include "Standard Checks.h"


#include "Standard Algorithm.h"


void StandardAlgorithm::Solve(BoardInformation::BoardData &board)
{
    bool changed = true;


    while (changed)
    {
        changed = false;

        changed = CheckSingleOptions(board) || changed;
    }

    // Will try to guess a spot (but only if it still possible)
    if (!IsSolved(board) && !IsImpossible(board))
        GuessSpot(board);

}



bool StandardAlgorithm::CheckSingleOptions(BoardInformation::BoardData &board)
{
    bool changed = false;

    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            // Should only look for a number that can be replaced if there is currently no number there
            if (!board.board[x][y])
            {
                size_t num = BoardInformation::GetOnlyNumberCanBePlaced(board, x, y);

                if (num)
                {
                    board.board[x][y] = num;

                    BoardInformation::UpdatePossibleSpots(board, num, x, y);

                    changed = true;
                }
            }
        }
    }

    return changed;
}