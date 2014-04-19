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
    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            if (tempBoard.board[x][y])
                ASSERT_EQ(tempBoard.board[x][y], board.board[x][y]);
        }
    }

    // The value of the unknown spots
    ASSERT_EQ(1, board.board[0][0]);
    ASSERT_EQ(5, board.board[1][1]);
    ASSERT_EQ(9, board.board[2][2]);
    ASSERT_EQ(5, board.board[3][3]);
    ASSERT_EQ(9, board.board[4][4]);
    ASSERT_EQ(4, board.board[5][5]);
    ASSERT_EQ(9, board.board[6][6]);
    ASSERT_EQ(4, board.board[7][7]);
    ASSERT_EQ(8, board.board[8][8]);

    ASSERT_EQ(9, board.board[8][0]);
    ASSERT_EQ(2, board.board[7][1]);
    ASSERT_EQ(4, board.board[6][2]);
    ASSERT_EQ(7, board.board[5][3]);
    ASSERT_EQ(9, board.board[4][4]);
    ASSERT_EQ(2, board.board[3][5]);
    ASSERT_EQ(5, board.board[2][6]);
    ASSERT_EQ(7, board.board[1][7]);
    ASSERT_EQ(9, board.board[0][8]);
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
    for (size_t x = 0; x < board.boardSize; ++x)
    {
        for (size_t y = 0; y < board.boardSize; ++y)
        {
            if (tempBoard.board[x][y])
                ASSERT_EQ(tempBoard.board[x][y], board.board[x][y]);
        }
    }

    // The value of the unknown spots. Could be either one
    if (board.board[2][0] == 3)
    {
        ASSERT_EQ(4, board.board[3][0]);

        ASSERT_EQ(4, board.board[2][2]);
        ASSERT_EQ(3, board.board[3][2]);
    }
    
    else
    {
        ASSERT_EQ(4, board.board[2][0]);
        ASSERT_EQ(3, board.board[3][0]);

        ASSERT_EQ(3, board.board[2][2]);
        ASSERT_EQ(4, board.board[3][2]);
    }
}





TEST(StandardAlgorithmTests, RowSingleTest)
{
    BoardData board;

    ASSERT_TRUE(LoadBoard(board, "unsolved_row", "../../Unit Tests/examples.txt"));

    StandardAlgorithm algo;
    algo.BeginSolving(board);

    // Much of puzzle will be guessed, but it should still be solved
    ASSERT_TRUE(IsSolved(board));

    // These two points are forced due to be being only possible row
    ASSERT_EQ(1, board.board[6][1]);

    ASSERT_EQ(2, board.board[6][0]);
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
    ASSERT_EQ(3, board.board[1][8]);

    ASSERT_EQ(4, board.board[0][8]);
}


TEST(StandardAlgorithmTests, RowAndColumnSingleTest)
{
    BoardData board;

    ASSERT_TRUE(LoadBoard(board, "unsolved_rowAndColumn", "../../Unit Tests/examples.txt"));

    StandardAlgorithm algo;
    algo.BeginSolving(board);

    // Much of puzzle will be guessed, but it should still be solved
    ASSERT_TRUE(IsSolved(board));

    // These two points are forced due to be being only possible row
    ASSERT_EQ(1, board.board[6][1]);

    ASSERT_EQ(2, board.board[6][0]);

    // These two points are forced due to be being only possible column
    ASSERT_EQ(3, board.board[1][8]);

    ASSERT_EQ(4, board.board[0][8]);
}