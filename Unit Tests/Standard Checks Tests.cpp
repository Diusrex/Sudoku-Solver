#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Standard Checks.h"
#include "../Sudoku Implementation/Code/Load Board.h"

using namespace BoardInformation;

#include <direct.h>
#define GetCurrentDir _getcwd

TEST(IsSolvedTests, IsNotSolved)
{
    BoardData board;
    board.SetUp(3);

    ASSERT_FALSE(IsSolved(board));

    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "unsolved", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_FALSE(IsSolved(board));
}





TEST(IsSolvedTests, IsSolved)
{
    BoardData board;
    
    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "solved", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_TRUE(IsSolved(board));
}





TEST(IsImpossibleTests, IsPossible)
{
    BoardData board;

    board.SetUp(2);
    ASSERT_FALSE(IsImpossible(board));

    // This would represent not being able to be placed in top left, and bottom right of top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][1][1] = false;

    // This would represent having claimed the top right box for 2
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[2][0][1] = false;
    board.canBePlacedIn[2][1][1] = false;
    board.canBePlacedIn[2][1][0] = false;
    board.numberPlacedInBox[2][0][0] = true;

    ASSERT_FALSE(IsImpossible(board));
}




TEST(IsImpossibleTests, IsImPossible)
{
    BoardData board;

    board.SetUp(2);

    // This would represent not being able to be placed in top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][0][1] = false;
    board.canBePlacedIn[1][1][0] = false;
    board.canBePlacedIn[1][1][1] = false;
    ASSERT_TRUE(IsImpossible(board));
}