#include "Board Data.h"
#include "Standard Checks.h"

#include <vector>

#include "Standard Algorithm.h"


void StandardAlgorithm::Solve(BoardInformation::BoardData &board)
{
    bool changed = true;


    while (changed)
    {
        changed = false;

        changed = CheckSingleOptions(board) || changed;

        changed = CheckRowAndColumnOptions(board) || changed;
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



bool StandardAlgorithm::CheckRowAndColumnOptions(BoardInformation::BoardData &board)
{
    bool changed = false;

    for (size_t linePos = 0; linePos < board.boardSize; ++linePos)
    {
        std::vector<int> rowOnlyPos(board.boardSize + 1), columnOnlyPos(board.boardSize + 1);
        std::vector<bool> singleOccuranceInRow(board.boardSize + 1), singleOccuranceInColumn(board.boardSize + 1);

        BoardInformation::GetRowAndColumnOnlyPossible(board, linePos, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

        // Now go through each number, and check to see if it occured in a single pos
        for (size_t num = 1; num <= board.boardSize; ++num)
        {
            // Row handling
            if (singleOccuranceInRow[num])
            {
                board.board[linePos][rowOnlyPos[num]] = num;

                BoardInformation::UpdatePossibleSpots(board, num, linePos, rowOnlyPos[num]);

                changed = true;
            }

            if (singleOccuranceInColumn[num])
            {
                board.board[columnOnlyPos[num]][linePos] = num;

                BoardInformation::UpdatePossibleSpots(board, num, columnOnlyPos[num], linePos);

                changed = true;
            }
        }
    }

    return changed;
}

