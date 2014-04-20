#include <iostream>

#include "Board Data.h"



using namespace std;



void BoardInformation::BoardData::SetUpSizes(size_t newBoxSize)
{
    sectionSize = newBoxSize;
    boardSize = sectionSize * sectionSize;
    board.resize(boardSize, vector<int>(boardSize, 0));
    canBePlacedIn.resize(boardSize + 1, vector<vector<bool>>(boardSize, vector<bool>(boardSize, true)));
    numberPlacedInSection.resize(boardSize + 1, vector<vector<bool>>(boardSize, vector<bool>(boardSize, false)));
}



void BoardInformation::BoardData::PrintOut() const
{
    cout << "\n\n";
    cout << "   0 1 2   3 4 5   6 7 8\n"
        << " +-------|-------|------\n";

    for (size_t y = 0; y < boardSize; ++y)
    {
        for (size_t x = 0; x < boardSize; ++x)
        {
            // Should have a separator
            if ((x % 3 == 0) && (x != 0))
            {
                cout << "| ";
            }

            // Some special behavior
            else if (x == 0)
            {
                // Print out the horizontal line
                if ((y % 3 == 0) && (y != 0))
                    cout << " |-------|-------|------\n";

                cout << " | ";
            }

            cout << board[x][y] << ' ';
        }

        cout << '\n';
    }

    cout << '\n';
}





bool BoardInformation::BoardData::SetUpPossibleSpots()
{
    for (size_t x = 0; x < boardSize; ++x)
    {
        for (size_t y = 0; y < boardSize; ++y)
        {
            if (board[x][y] != 0)
            {
                size_t number = board[x][y];
                size_t sectionX = ConvertFromPositionToSection(*this, x), sectionY = ConvertFromPositionToSection(*this, y);


                // Is to check to see if this spot has already been taken, if it has then the graph is not valid
                if (!canBePlacedIn[number][x][y] || numberPlacedInSection[number][sectionX][sectionY])
                {
                    return false;
                }

                UpdatePossibleSpots(x, y, number);
            }
        }
    }

    return true;
}




void BoardInformation::BoardData::SetBox(const size_t x, const size_t y, const size_t takenNum)
{
    board[x][y] = takenNum;
    UpdatePossibleSpots(x, y, takenNum);
}




void SetRowAndColumnToFalse(vector<vector<bool>>& grid, size_t x, size_t y)
{
    for (size_t pos = 0; pos < grid.size(); ++pos)
    {
        grid[x][pos] = false;
        grid[pos][y] = false;
    }
}




// Will set the grid for the given num in the given section to false
void SetSectionToFalse(vector<vector<bool>>& grid, const size_t xOffset, const size_t yOffset, const size_t sectionSize)
{
    for (size_t xc = 0; xc < sectionSize; ++xc)
    {
        for (size_t yc = 0; yc < sectionSize; ++yc)
        {
            grid[xOffset + xc][yOffset + yc] = false;
        }
    }
}





void BoardInformation::BoardData::UpdatePossibleSpots(const size_t x, const size_t y, const size_t takenNum)
{

    SetRowAndColumnToFalse(canBePlacedIn[takenNum], x, y);
    
    const size_t sectionX = ConvertFromPositionToSection(*this, x);
    const size_t sectionY = ConvertFromPositionToSection(*this, y);

    numberPlacedInSection[takenNum][sectionX][sectionY] = true;
    
    SetSectionToFalse(canBePlacedIn[takenNum], ConvertFromSectionToSectionOffset(*this, sectionX), ConvertFromSectionToSectionOffset(*this, sectionY), sectionSize);

    
    // No other number may be placed in the given box
    for (size_t tempNum = 1; tempNum < GetNumberOfPossibleNumbers(); ++tempNum)
        canBePlacedIn[tempNum][x][y] = false;
}








size_t BoardInformation::ConvertFromPositionToSection(const BoardData& board, size_t pos)
{
    return pos / board.GetSectionSize();
}


size_t BoardInformation::ConvertFromPositionToSectionOffset(const BoardData& board, size_t pos)
{
    return ConvertFromPositionToSection(board, pos) * board.GetSectionSize();
}

size_t BoardInformation::ConvertFromSectionToSectionOffset(const BoardData& board, size_t sectionPos)
{
    return sectionPos * board.GetSectionSize();
}
