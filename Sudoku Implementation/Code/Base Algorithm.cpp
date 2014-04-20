#include "Board Data.h"
#include "Standard Checks.h"

#include "Base Algorithm.h"


bool Algorithm::BeginSolving(BoardInformation::BoardData & board)
{
    // This will be false if the board was not valid
    if (!board.SetUpPossibleSpots())
        return false;

    Solve(board);

    return true;
}


void Algorithm::GuessSpot(BoardInformation::BoardData & board)
{
    for (size_t y = 0; y < board.GetBoardSize(); ++y)
    {
        for (size_t x = 0; x < board.GetBoardSize(); ++x)
        {
            if (board.GetNumberAtPosition(x, y) == 0)
            {
                // Guess all possible numbers that can be here
                for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
                {
                    if (board.GetCanBePlacedAtPosition(x, y, num))
                    {
                        // Need to create copies
                        BoardInformation::BoardData tempBoard = board;

                        tempBoard.SetBox(x, y, num);

                        Solve(tempBoard);

                        if (IsSolved(tempBoard))
                        {
                            board = tempBoard;
                            return;
                        }


                    }
                }

                // Should only guess at one spot
                return;
            }
        }
    }
}