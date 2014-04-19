#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"

using namespace BoardInformation;

TEST(BoardDataTest, ProperCreationSize)
{
    BoardData data;
    data.SetUpSizes(3);

    ASSERT_EQ(3, data.boxSize);
    ASSERT_EQ(9, data.boardSize);
    ASSERT_EQ(9, data.board.size());
    ASSERT_EQ(9, data.board[0].size());

    
    ASSERT_EQ(10, data.canBePlacedIn.size());
    ASSERT_EQ(9, data.canBePlacedIn[0].size());
    ASSERT_EQ(9, data.canBePlacedIn[0][0].size());
    
    ASSERT_EQ(10, data.numberPlacedInSection.size());
    ASSERT_EQ(9, data.numberPlacedInSection[0].size());
    ASSERT_EQ(9, data.numberPlacedInSection[0][0].size());
}



TEST(BoardDataTest, ProperCreationBoard)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);

    for (int x = 0; x < boxSize * boxSize; ++x)
        for (int y = 0; y < boxSize * boxSize; ++y)
            ASSERT_EQ(0, data.board[x][y]);
}



TEST(BoardDataTest, ExtraData)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < boxSize * boxSize; ++x)
            for (int y = 0; y < boxSize * boxSize; ++y)
                ASSERT_TRUE(data.canBePlacedIn[num][x][y]);

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < boxSize * boxSize; ++x)
            for (int y = 0; y < boxSize * boxSize; ++y)
                ASSERT_FALSE(data.numberPlacedInSection[num][x][y]);
}



TEST(SetUpPossibleSpotsTests, NoPlacedTest)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);

    ASSERT_TRUE(SetUpPossibleSpots(data));

    // Everything must be placeable in
    for (int num = 1; num < 10; ++num)
    {
        for (size_t x = 0; x < data.boardSize; ++x)
        {
            for (size_t y = 0; y < data.boardSize; ++y)
            {
                ASSERT_TRUE(data.canBePlacedIn[num][x][y]);
            }
        }
    }

    for (int num = 1; num < 10; ++num)
    {
        for (size_t boxX = 0; boxX < data.boxSize; ++boxX)
        {
            for (size_t boxY = 0; boxY < data.boxSize; ++boxY)
            {
                ASSERT_FALSE(data.numberPlacedInSection[num][boxY][boxY]);
            }
        }
    }
}




TEST(SetUpPossibleSpotsTests, ValidBoardTest)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);
    data.board[0][0] = 1;

    ASSERT_TRUE(SetUpPossibleSpots(data));

    // Check to see if the section was claimed, 
    ASSERT_TRUE(data.numberPlacedInSection[1][0][0]);


    for (size_t num = 2; num <= 9; ++num)
        ASSERT_FALSE(data.canBePlacedIn[num][0][0]);

    // Only a single column and single row are changed
    for (size_t pos = 0; pos < 9; ++pos)
    {
        ASSERT_FALSE(data.canBePlacedIn[1][pos][0]);
        ASSERT_FALSE(data.canBePlacedIn[1][0][pos]);
    }
}



TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Row)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);
    data.board[0][0] = 1;
    data.board[1][0] = 1;
    ASSERT_FALSE(SetUpPossibleSpots(data));
}




TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Column)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);
    data.board[0][0] = 1;
    data.board[0][1] = 1;
    ASSERT_FALSE(SetUpPossibleSpots(data));
}




TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Section)
{
    int boxSize = 3;
    BoardData data;
    data.SetUpSizes(boxSize);
    data.board[0][0] = 1;
    data.board[1][1] = 1;
    ASSERT_FALSE(SetUpPossibleSpots(data));
}



TEST(UpdatePossibleSpotsTest, CompleteTest)
{
    BoardData data;
    data.SetUpSizes(3);

    data.board[0][0] = 1;
    UpdatePossibleSpots(data, 1, 0, 0);

    // Check to see if the section was claimed, 
    ASSERT_TRUE(data.numberPlacedInSection[1][0][0]);

    
    for (size_t num = 2; num <= 9; ++num)
        ASSERT_FALSE(data.canBePlacedIn[num][0][0]);
    
    // Only a single column and single row are changed
    for (size_t pos = 0; pos < 9; ++pos)
    {
        ASSERT_FALSE(data.canBePlacedIn[1][pos][0]);
        ASSERT_FALSE(data.canBePlacedIn[1][0][pos]);
    }
}