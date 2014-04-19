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





bool BoardInformation::IsImpossible(const BoardData & board)
{
    for (size_t num = 1; num < board.boardSize + 1; ++num)
    {
        for (size_t boxX = 0; boxX < board.boardSize / board.boxSize; ++boxX)
        {
            for (size_t boxY = 0; boxY < board.boardSize / board.boxSize; ++boxY)
            {
                if (!board.numberPlacedInSection[num][boxX][boxY])
                {
                    bool atLeastOneSpot = false;

                    size_t baseX = boxX * board.boxSize;
                    size_t baseY = boxY * board.boxSize;

                    for (size_t xc = 0; xc < board.boxSize; ++xc)
                    {
                        for (size_t yc = 0; yc < board.boxSize; ++yc)
                        {
                            if (board.canBePlacedIn[num][baseX + xc][baseY + yc])
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

    for (size_t currentNumber = 1; currentNumber <= board.boardSize; ++currentNumber)
    {
        if (board.canBePlacedIn[currentNumber][x][y])
        {
            // Another number could be placed
            if (num)
                return 0;

            num = currentNumber;
        }
    }

    return num;
}






void BoardInformation::GetRowAndColumnOnlyPossible(const BoardData & board, const size_t linePos, std::vector<int>& rowOnlyPos, std::vector<bool>& singleOccuranceInRow, std::vector<int>& columnOnlyPos, std::vector<bool>& singleOccuranceInColumn)
{
    for (size_t num = 1; num <= board.boardSize; ++num)
    {
        bool multipleOccurancesInRow = false;
        bool multipleOccurancesInColumn = false;
        singleOccuranceInRow[num] = false;
        singleOccuranceInColumn[num] = false;

        for (size_t otherPos = 0; otherPos < board.boardSize; ++otherPos)
        {
            // Row code
            if (board.canBePlacedIn[num][linePos][otherPos] && !multipleOccurancesInRow)
            {
                if (singleOccuranceInRow[num])
                {
                    singleOccuranceInRow[num] = false;
                    multipleOccurancesInRow = true;
                }

                else
                {
                    rowOnlyPos[num] = otherPos;
                    singleOccuranceInRow[num] = true;
                }
            }


            // Column code
            if (board.canBePlacedIn[num][otherPos][linePos] && !multipleOccurancesInColumn)
            {
                if (singleOccuranceInColumn[num])
                {
                    singleOccuranceInColumn[num] = false;
                    multipleOccurancesInColumn = true;
                }
                else
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
    size_t xOffset = sectionX * board.boxSize;
    size_t yOffset = sectionY * board.boxSize;

    for (size_t num = 1; num <= board.boardSize; ++num)
    {
        singleOccuranceInSection[num] = false;

        // Only matters if the number can be placed in
        if (!board.numberPlacedInSection[num][sectionX][sectionY])
        {
            bool multipleOccurances = false;

            for (size_t x = 0; x < board.boxSize; ++x)
            {
                for (size_t y = 0; y < board.boxSize; ++y)
                {
                    if (board.canBePlacedIn[num][xOffset + x][yOffset + y])
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