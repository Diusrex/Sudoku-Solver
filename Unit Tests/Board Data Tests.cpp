#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"

using namespace BoardInformation;

TEST(BoardDataTest, ProperCreationSize)
{
    BoardData data;
    data.SetUp(3);

    ASSERT_EQ(3, data.boxSize);
    ASSERT_EQ(9, data.boardSize);
    ASSERT_EQ(9, data.board.size());
    ASSERT_EQ(9, data.board[0].size());

    
    ASSERT_EQ(10, data.canBePlacedIn.size());
    ASSERT_EQ(9, data.canBePlacedIn[0].size());
    ASSERT_EQ(9, data.canBePlacedIn[0][0].size());
    
    ASSERT_EQ(10, data.numberPlacedInBox.size());
    ASSERT_EQ(9, data.numberPlacedInBox[0].size());
    ASSERT_EQ(9, data.numberPlacedInBox[0][0].size());
}



TEST(BoardDataTest, ProperCreationBoard)
{
    int boxSize = 3;
    BoardData data;
    data.SetUp(boxSize);

    for (int x = 0; x < boxSize * boxSize; ++x)
        for (int y = 0; y < boxSize * boxSize; ++y)
            ASSERT_EQ(0, data.board[x][y]);
}



TEST(BoardDataTest, ExtraData)
{
    int boxSize = 3;
    BoardData data;
    data.SetUp(boxSize);

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < boxSize * boxSize; ++x)
            for (int y = 0; y < boxSize * boxSize; ++y)
                ASSERT_TRUE(data.canBePlacedIn[num][x][y]);

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < boxSize * boxSize; ++x)
            for (int y = 0; y < boxSize * boxSize; ++y)
                ASSERT_FALSE(data.numberPlacedInBox[num][x][y]);
}