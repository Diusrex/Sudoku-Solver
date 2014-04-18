#include <iostream>

#include "Board Data.h"



using namespace std;



void BoardInformation::BoardData::SetUp(size_t newBoxSize)
{
    boxSize = newBoxSize;
    boardSize = boxSize * boxSize;
    board.resize(boardSize, vector<int>(boardSize, 0));
    canBePlacedIn.resize(boardSize + 1, vector<vector<bool>>(boardSize, vector<bool>(boardSize, true)));
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

