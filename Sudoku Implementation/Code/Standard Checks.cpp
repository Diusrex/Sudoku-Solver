#include "Board Data.h"

#include "Standard Checks.h"

bool BoardInformation::IsSolved(const BoardData& board)
{
    for (size_t x = 0; x < board.GetBoardSize(); ++x)
    {
        for (size_t y = 0; y < board.GetBoardSize(); ++y)
        {
            if (!board.GetNumberAtPosition(x, y))
                return false;
        }
    }

    return true;
}





bool BoardInformation::IsImpossible(const BoardData & board)
{
    for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
    {
        for (size_t sectionX = 0; sectionX < board.GetNumberOfSections(); ++sectionX)
        {
            for (size_t sectionY = 0; sectionY < board.GetNumberOfSections(); ++sectionY)
            {
                if (!board.GetNumberPlacedInSection(sectionX, sectionY, num))
                {
                    bool atLeastOneSpot = false;

                    size_t baseX = ConvertFromSectionToSectionOffset(board, sectionX);
                    size_t baseY = ConvertFromSectionToSectionOffset(board, sectionY);

                    for (size_t xc = 0; xc < board.GetSectionSize(); ++xc)
                    {
                        for (size_t yc = 0; yc < board.GetSectionSize(); ++yc)
                        {
                            if (board.GetCanBePlacedAtPosition(baseX + xc, baseY + yc, num))
                                atLeastOneSpot = true;
                        }
                    }

                    if (!atLeastOneSpot)
                    {
                        return true;
                    }

                }
            }
        }
    }

    return false;
}




size_t BoardInformation::GetOnlyNumberCanBePlaced(const BoardData & board, size_t x, size_t y)
{
    size_t num = 0;

    for (size_t currentNumber = 1; currentNumber < board.GetNumberOfPossibleNumbers(); ++currentNumber)
    {
        if (board.GetCanBePlacedAtPosition(x, y, currentNumber))
        {
            // Another number could be placed. Can do this because currentNumber >= 1
            if (num)
                return 0;

            num = currentNumber;
        }
    }

    return num;
}






void BoardInformation::GetRowAndColumnOnlyPossible(const BoardData & board, const size_t linePos, std::vector<int>& rowOnlyPos, std::vector<bool>& singleOccuranceInRow, std::vector<int>& columnOnlyPos, std::vector<bool>& singleOccuranceInColumn)
{
    for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
    {
        bool multipleOccurancesInRow = false;
        bool multipleOccurancesInColumn = false;
        singleOccuranceInRow[num] = false;
        singleOccuranceInColumn[num] = false;

        for (size_t otherPos = 0; otherPos < board.GetBoardSize(); ++otherPos)
        {
            if (board.GetCanBePlacedAtPosition(otherPos, linePos, num) && !multipleOccurancesInRow)
            {
                if (singleOccuranceInRow[num])
                {
                    singleOccuranceInRow[num] = false;
                    multipleOccurancesInRow = true;
                }

                else if (!multipleOccurancesInRow)
                {
                    rowOnlyPos[num] = otherPos;
                    singleOccuranceInRow[num] = true;
                }
            }


            // Column code
            if (board.GetCanBePlacedAtPosition(linePos, otherPos, num) && !multipleOccurancesInColumn)
            {
                if (singleOccuranceInColumn[num])
                {
                    singleOccuranceInColumn[num] = false;
                    multipleOccurancesInColumn = true;
                }

                else if (!multipleOccurancesInColumn)
                {
                    columnOnlyPos[num] = otherPos;
                    singleOccuranceInColumn[num] = true;
                }
            }
        }
    }
}





void BoardInformation::GetSectionOnlyPossible(const BoardData & board, const size_t sectionX, const size_t sectionY, std::vector<std::pair<size_t, size_t>>& positionInSection, std::vector<bool>& singleOccuranceInSection)
{
    size_t xOffset = ConvertFromSectionToSectionOffset(board, sectionX);
    size_t yOffset = ConvertFromSectionToSectionOffset(board, sectionY);

    for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
    {
        singleOccuranceInSection[num] = false;

        // Only matters if the number can be placed in
        if (!board.GetNumberPlacedInSection(sectionX, sectionY, num))
        {
            bool multipleOccurances = false;

            for (size_t x = 0; x < board.GetSectionSize(); ++x)
            {
                for (size_t y = 0; y < board.GetSectionSize(); ++y)
                {
                    if (board.GetCanBePlacedAtPosition(xOffset + x, yOffset + y, num))
                    {
                        if (singleOccuranceInSection[num])
                        {
                            multipleOccurances = true;
                            singleOccuranceInSection[num] = false;
                        }

                        else if (!multipleOccurances)
                        {
                            singleOccuranceInSection[num] = true;
                            positionInSection[num].first = x;
                            positionInSection[num].second = y;
                        }
                    }
                }
            }
        }
    }

}