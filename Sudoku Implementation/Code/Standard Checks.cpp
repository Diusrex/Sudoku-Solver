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
