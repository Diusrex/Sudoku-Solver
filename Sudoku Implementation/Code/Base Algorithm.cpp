#include "Board Data.h"
#include "Standard Checks.h"

#include "Base Algorithm.h"


bool Algorithm::BeginSolving(BoardInformation::BoardData & board)
{
    // This will be false if the board was not valid
    if (!BoardInformation::SetUpPossibleSpots(board))
        return false;

    Solve(board);

    return true;
}


void Algorithm::GuessSpot(BoardInformation::BoardData & board)
{
    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            if (board.board[x][y] == 0)
            {
                // Guess all possible numbers that can be here
                for (size_t num = 1; num <= board.boardSize; ++num)
                {
                    if (board.canBePlacedIn[num][x][y])
                    {
                        // Need to create copies
                        BoardInformation::BoardData tempBoard = board;

                        tempBoard.board[x][y] = num;

                        UpdatePossibleSpots(tempBoard, num, x, y);

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