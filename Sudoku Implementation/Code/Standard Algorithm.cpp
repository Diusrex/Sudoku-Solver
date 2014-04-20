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

        changed = CheckSectionOptions(board) || changed;
    }
    
    
    // Will try to guess a spot (but only if it still possible)
    if (!IsSolved(board) && !IsImpossible(board))
        GuessSpot(board);

}



bool StandardAlgorithm::CheckSingleOptions(BoardInformation::BoardData &board)
{
    bool changed = false;

    for (size_t x = 0; x < board.GetBoardSize(); ++x)
    {
        for (size_t y = 0; y < board.GetBoardSize(); ++y)
        {
            // Should only look for a number that can be replaced if there is currently no number there
            if (!board.GetNumberAtPosition(x, y))
            {
                size_t num = BoardInformation::GetOnlyNumberCanBePlaced(board, x, y);

                if (num)
                {
                    board.SetBox(x, y, num);

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

    for (size_t linePos = 0; linePos < board.GetBoardSize(); ++linePos)
    {
        std::vector<int> rowOnlyPos(board.GetNumberOfPossibleNumbers()), columnOnlyPos(board.GetNumberOfPossibleNumbers());
        std::vector<bool> singleOccuranceInRow(board.GetNumberOfPossibleNumbers()), singleOccuranceInColumn(board.GetNumberOfPossibleNumbers());

        BoardInformation::GetRowAndColumnOnlyPossible(board, linePos, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

        // Now go through each number, and check to see if it occured in a single pos
        for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
        {
            // Row handling
            if (singleOccuranceInRow[num])
            {
                board.SetBox(rowOnlyPos[num], linePos, num);

                changed = true;
            }

            if (singleOccuranceInColumn[num])
            {
                board.SetBox(linePos, columnOnlyPos[num], num);

                changed = true;
            }
        }
    }

    return changed;
}





bool StandardAlgorithm::CheckSectionOptions(BoardInformation::BoardData &board)
{
    bool changed = false;

    for (size_t sectionX = 0; sectionX < board.GetSectionSize(); ++sectionX)
    {
        for (size_t sectionY = 0; sectionY < board.GetSectionSize(); ++sectionY)
        {
            std::vector<std::pair<size_t, size_t>> positionInSection(board.GetNumberOfPossibleNumbers());
            std::vector<bool> singleOccuranceInSection(board.GetNumberOfPossibleNumbers());

            BoardInformation::GetSectionOnlyPossible(board, sectionX, sectionY, positionInSection, singleOccuranceInSection);

            for (size_t num = 1; num <= board.GetBoardSize(); ++num)
            {
                if (singleOccuranceInSection[num])
                {
                    size_t x = BoardInformation::ConvertFromSectionToSectionOffset(board, sectionX) + positionInSection[num].first;
                    size_t y = BoardInformation::ConvertFromSectionToSectionOffset(board, sectionY) + positionInSection[num].second;

                    board.SetBox(x, y, num);

                    changed = true;
                }
            }
        }
    }

    return changed;
}
