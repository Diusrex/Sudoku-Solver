#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Load Board.h"
#include "../Sudoku Implementation/Code/Standard Algorithm.h"
#include "../Sudoku Implementation/Code/Standard Checks.h"

using namespace BoardInformation;

// Is the absolute most basic test
TEST(StandardAlgorithmTests, SingleSpotTest)
{
    BoardData board;

    // No point in continuing if this fails
    ASSERT_TRUE(LoadBoard(board, "unsolved_doubleDiagonal", "../../Unit Tests/examples.txt"));

    BoardData tempBoard = board;

    StandardAlgorithm algo;

    algo.BeginSolving(board);

    // Ensure that the algo didn't alter the board, other than the single spot
    for (size_t x = 0; x < board.GetBoardSize(); ++x)
    {
        for (size_t y = 0; y < board.GetBoardSize(); ++y)
        {
            if (tempBoard.GetNumberAtPosition(x, y))
                ASSERT_EQ(tempBoard.GetNumberAtPosition(x, y), board.GetNumberAtPosition(x, y));
        }
    }

    // The value of the unknown spots
    ASSERT_EQ(1, board.GetNumberAtPosition(0, 0));
    ASSERT_EQ(5, board.GetNumberAtPosition(1, 1));
    ASSERT_EQ(9, board.GetNumberAtPosition(2, 2));
    ASSERT_EQ(5, board.GetNumberAtPosition(3, 3));
    ASSERT_EQ(9, board.GetNumberAtPosition(4, 4));
    ASSERT_EQ(4, board.GetNumberAtPosition(5, 5));
    ASSERT_EQ(9, board.GetNumberAtPosition(6, 6));
    ASSERT_EQ(4, board.GetNumberAtPosition(7, 7));
    ASSERT_EQ(8, board.GetNumberAtPosition(8, 8));

    ASSERT_EQ(9, board.GetNumberAtPosition(8, 0));
    ASSERT_EQ(2, board.GetNumberAtPosition(7, 1));
    ASSERT_EQ(4, board.GetNumberAtPosition(6, 2));
    ASSERT_EQ(7, board.GetNumberAtPosition(5, 3));
    ASSERT_EQ(9, board.GetNumberAtPosition(4, 4));
    ASSERT_EQ(2, board.GetNumberAtPosition(3, 5));
    ASSERT_EQ(5, board.GetNumberAtPosition(2, 6));
    ASSERT_EQ(7, board.GetNumberAtPosition(1, 7));
    ASSERT_EQ(9, board.GetNumberAtPosition(0, 8));
}





TEST(StandardAlgorithmTests, GuessTest)
{
    BoardData board;

    // No point in continuing if this fails
    ASSERT_TRUE(LoadBoard(board, "unsolved_guess", "../../Unit Tests/examples.txt"));

    BoardData tempBoard = board;

    StandardAlgorithm algo;

    algo.BeginSolving(board);

    // Ensure that the algo didn't alter the board, other than the single spot
    for (size_t x = 0; x < board.GetBoardSize(); ++x)
    {
        for (size_t y = 0; y < board.GetBoardSize(); ++y)
        {
            if (tempBoard.GetNumberAtPosition(x, y))
                ASSERT_EQ(tempBoard.GetNumberAtPosition(x, y), board.GetNumberAtPosition(x, y));
        }
    }

    // The value of the unknown spots. Could be either one
    if (board.GetNumberAtPosition(2, 0) == 3)
    {
        ASSERT_EQ(4, board.GetNumberAtPosition(3, 0));

        ASSERT_EQ(4, board.GetNumberAtPosition(2, 2));
        ASSERT_EQ(3, board.GetNumberAtPosition(3, 2));
    }
    
    else
    {
        ASSERT_EQ(4, board.GetNumberAtPosition(2, 0));
        ASSERT_EQ(3, board.GetNumberAtPosition(3, 0));

        ASSERT_EQ(3, board.GetNumberAtPosition(2, 2));
        ASSERT_EQ(4, board.GetNumberAtPosition(3, 2));
    }
}





TEST(StandardAlgorithmTests, RowSingleTest)
{
    BoardData board;

    ASSERT_TRUE(LoadBoard(board, "unsolved_row", "../../Unit Tests/examples.txt"));

    // This one is not meant to be solvable
    StandardAlgorithm algo;
    algo.BeginSolving(board);

    // Much of puzzle will be guessed, but it should still be solved
    ASSERT_TRUE(IsSolved(board));

    // These two points are forced due to be being only possible row
    ASSERT_EQ(1, board.GetNumberAtPosition(6, 1));

    ASSERT_EQ(2, board.GetNumberAtPosition(6, 0));
}





TEST(StandardAlgorithmTests, ColumnSingleTest)
{
    BoardData board;

    ASSERT_TRUE(LoadBoard(board, "unsolved_column", "../../Unit Tests/examples.txt"));
    
    StandardAlgorithm algo;
    algo.BeginSolving(board);

    // Much of puzzle will be guessed, but it should still be solved
    ASSERT_TRUE(IsSolved(board));

    // These two points are forced due to be being only possible column
    ASSERT_EQ(3, board.GetNumberAtPosition(1, 8));

    ASSERT_EQ(4, board.GetNumberAtPosition(0, 8));
}


TEST(StandardAlgorithmTests, RowAndColumnSingleTest)
{
    BoardData board;

    ASSERT_TRUE(LoadBoard(board, "unsolved_rowAndColumn", "../../Unit Tests/examples.txt"));

    // This one is not meant to be solvable
    StandardAlgorithm algo;
    ASSERT_TRUE(algo.BeginSolving(board));

    // These two points are forced due to be being only possible row
    ASSERT_EQ(1, board.GetNumberAtPosition(6, 1));

    ASSERT_EQ(2, board.GetNumberAtPosition(6, 0));

    // These two points are forced due to be being only possible column
    ASSERT_EQ(3, board.GetNumberAtPosition(1, 8));

    ASSERT_EQ(4, board.GetNumberAtPosition(0, 8));
}




TEST(StandardAlgorithmTests, SectionBasicTest)
{
    BoardData board;

    // If either of these are false, then no point in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section", "../../Unit Tests/examples.txt"));
    
    StandardAlgorithm algo;

    ASSERT_TRUE(algo.BeginSolving(board));
    
    // Is one of a few guaranteed spots
    ASSERT_EQ(1, board.GetNumberAtPosition(0, 0));
    ASSERT_EQ(2, board.GetNumberAtPosition(2, 2));
    ASSERT_EQ(3, board.GetNumberAtPosition(2, 0));
}



TEST(StandardAlgorithmTests, SectionOffsetTest)
{
    BoardData board;

    // If either of these are false, then no poin in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section_offset", "../../Unit Tests/examples.txt"));
    
    StandardAlgorithm algo;

    ASSERT_TRUE(algo.BeginSolving(board));

    // Is one of a few guaranteed spots
    ASSERT_EQ(1, board.GetNumberAtPosition(5, 5));
    ASSERT_EQ(2, board.GetNumberAtPosition(3, 5));
    ASSERT_EQ(3, board.GetNumberAtPosition(3, 4));
}