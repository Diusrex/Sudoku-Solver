#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Standard Checks.h"
#include "../Sudoku Implementation/Code/Load Board.h"

using namespace BoardInformation;

#include <direct.h>
#define GetCurrentDir _getcwd

TEST(StandardChecks, IsNotSolved)
{
    BoardData board;
    board.SetUp(3);

    ASSERT_FALSE(IsSolved(board));

    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "unsolved", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_FALSE(IsSolved(board));
}


TEST(StandardChecks, IsSolved)
{
    BoardData board;
    
    // No point in the test continuing if this is false
    ASSERT_TRUE(LoadBoard(board, "solved", "../../Unit Tests/examples.txt")) << "The file 'examples.txt' does not contain the board 'unsolved'";

    ASSERT_TRUE(IsSolved(board));
}