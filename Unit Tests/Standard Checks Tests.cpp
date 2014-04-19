#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Standard Checks.h"
#include "../Sudoku Implementation/Code/Load Board.h"

using namespace BoardInformation;

TEST(IsSolvedTests, IsNotSolved)
{
    BoardData board;
    board.SetUpSizes(3);

    ASSERT_FALSE(IsSolved(board));

    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "unsolved_basic", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_FALSE(IsSolved(board));
}





TEST(IsSolvedTests, IsSolved)
{
    BoardData board;
    
    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "solved", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_TRUE(IsSolved(board));
}





TEST(IsImpossibleTests, IsPossibleTest)
{
    BoardData board;

    board.SetUpSizes(2);
    ASSERT_FALSE(IsImpossible(board));

    // This would represent not being able to be placed in top left, and bottom right of top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][1][1] = false;

    // This would represent having claimed the top right box for 2
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[2][0][1] = false;
    board.canBePlacedIn[2][1][1] = false;
    board.canBePlacedIn[2][1][0] = false;
    board.numberPlacedInSection[2][0][0] = true;

    ASSERT_FALSE(IsImpossible(board));
}




TEST(IsImpossibleTests, IsImpossibleTest)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would represent not being able to be placed in top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][0][1] = false;
    board.canBePlacedIn[1][1][0] = false;
    board.canBePlacedIn[1][1][1] = false;
    ASSERT_TRUE(IsImpossible(board));
}




TEST(GetOnlyNumberCanBePlacedTests, OneExists)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[3][0][0] = false;

    ASSERT_EQ(4, GetOnlyNumberCanBePlaced(board, 0, 0));
}



TEST(GetOnlyNumberCanBePlacedTests, MultipleOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}




TEST(GetOnlyNumberCanBePlacedTests, NoOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[4][0][0] = false;

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}