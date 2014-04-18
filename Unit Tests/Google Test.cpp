// Google Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"

TEST(BoardDataTest, EnsureProperSize)
{
    BoardData data;
    data.SetUp(3);

    ASSERT_EQ(3, data.boxSize);
    ASSERT_EQ(9, data.boardSize);
    ASSERT_EQ(9, data.board.size());
    ASSERT_EQ(9, data.board[0].size());
}