#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Load Board.h"

using namespace BoardInformation;

TEST(LoadingBoard, FileDoesntExist)
{
    BoardData tempBoard;
    ASSERT_FALSE(LoadBoard(tempBoard, "unsolved", "no way this exists.txt"));
}


TEST(LoadingBoard, PuzzleDoesntExist)
{
    BoardData tempBoard;
    ASSERT_FALSE(LoadBoard(tempBoard, "no way I made this", "../../Unit Tests/examples.txt"));
}





TEST(LoadingBoard, PuzzleExists)
{
    BoardData tempBoard;

    

    // Yea, pretty convoluted path
    ASSERT_TRUE(LoadBoard(tempBoard, "basic", "../../Unit Tests/examples.txt"));

    // The board basic is a 4 x 4, with the number = y * 4 + x + 1
    ASSERT_EQ(2, tempBoard.boxSize);
    ASSERT_EQ(4, tempBoard.boardSize);

    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            ASSERT_EQ(y * 4 + x + 1, tempBoard.board[x][y]);
        }
    }
}