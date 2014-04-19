#include <iostream>

#include "Board Data.h"



using namespace std;



void BoardInformation::BoardData::SetUpSizes(size_t newBoxSize)
{
    boxSize = newBoxSize;
    boardSize = boxSize * boxSize;
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





bool BoardInformation::SetUpPossibleSpots(BoardData & board)
{
    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            if (board.board[x][y] != 0)
            {
                size_t number = board.board[x][y];
                size_t boxX = x / board.boxSize, boxY = y / board.boxSize;


                // Is to check to see if this spot has already been taken, if it has then the graph is not valid
                if (!board.canBePlacedIn[number][x][y] || board.numberPlacedInSection[number][boxX][boxY])
                {
                    return false;
                }

                UpdatePossibleSpots(board, number, x, y);
            }
        }
    }

    return true;
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
void SetBoxToFalse(BoardInformation::BoardData & board, size_t takenNum, size_t sectionX, size_t sectionY)
{
    for (size_t xc = 0; xc < board.boxSize; ++xc)
    {
        for (size_t yc = 0; yc < board.boxSize; ++yc)
        {
            board.canBePlacedIn[takenNum][sectionX * board.boxSize + xc][sectionY * board.boxSize + yc] = false;
        }
    }
}




void BoardInformation::UpdatePossibleSpots(BoardData & board, size_t takenNum, size_t x, size_t y)
{
    size_t sectionX = x / board.boxSize, sectionY = y / board.boxSize;

    SetRowAndColumnToFalse(board.canBePlacedIn[takenNum], x, y);

    board.numberPlacedInSection[takenNum][sectionX][sectionY] = true;

    SetBoxToFalse(board, takenNum, sectionX, sectionY);

    // No other number may be placed in the given box
    for (size_t tempNum = 1; tempNum <= board.boardSize; ++tempNum)
        board.canBePlacedIn[tempNum][x][y] = false;
}