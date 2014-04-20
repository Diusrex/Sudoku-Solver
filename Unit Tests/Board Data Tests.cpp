#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"

namespace BoardInformation{
    TEST(BoardDataTest, ProperCreationSize)
    {
        BoardData data;
        data.SetUpSizes(3);

        ASSERT_EQ(3, data.GetSectionSize());
        ASSERT_EQ(9, data.GetBoardSize());
        ASSERT_EQ(10, data.GetNumberOfPossibleNumbers());
        ASSERT_EQ(3, data.GetNumberOfSections());

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
}

using namespace BoardInformation;


TEST(BoardDataTest, ProperCreationBoard)
{
    int sectionSize = 3;
    BoardData data;
    data.SetUpSizes(sectionSize);

    for (int x = 0; x < sectionSize * sectionSize; ++x)
        for (int y = 0; y < sectionSize * sectionSize; ++y)
            ASSERT_EQ(0, data.GetNumberAtPosition(x, y));
}



TEST(BoardDataTest, ExtraData)
{
    int sectionSize = 3;
    BoardData data;
    data.SetUpSizes(sectionSize);

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < sectionSize * sectionSize; ++x)
            for (int y = 0; y < sectionSize * sectionSize; ++y)
                ASSERT_TRUE(data.GetCanBePlacedAtPosition(x, y, num));

    for (int num = 1; num < 10; ++num)
        for (int x = 0; x < sectionSize; ++x)
            for (int y = 0; y < sectionSize; ++y)
                ASSERT_FALSE(data.GetNumberPlacedInSection(x, y, num));
}



TEST(BoardDataSetBoxTests, GeneralTest)
{
    size_t sectionSize = 3;
    BoardData data;
    data.SetUpSizes(sectionSize);

    size_t xTaken = 2, xSection = ConvertFromPositionToSection(data, xTaken);
    size_t yTaken = 2, ySection = ConvertFromPositionToSection(data, yTaken);
    data.SetBox(xTaken, yTaken, 1);
    ASSERT_EQ(1, data.GetNumberAtPosition(xTaken, yTaken));

    // Will go through all numbers
    for (size_t num = 1; num < data.GetNumberOfPossibleNumbers(); ++num)
    {
        for (size_t x = 0; x < data.GetBoardSize(); ++x)
        {
            for (size_t y = 0; y < data.GetBoardSize(); ++y)
            {
                // If num == 1, then the section, as well as horizontal and vertical lines should be false
                if (num == 1)
                {
                    if (x == xTaken || y == yTaken || (ConvertFromPositionToSection(data, x) == xSection && ConvertFromPositionToSection(data, y) == ySection))
                        ASSERT_FALSE(data.GetCanBePlacedAtPosition(x, y, num)) << x << y << num;
                    else
                        ASSERT_TRUE(data.GetCanBePlacedAtPosition(x, y, num)) << x << y << num;
                }

                // If num != 1, then only at (xTaken, yTaken) should it be false
                else
                {
                    if (x == xTaken && y == yTaken)
                        ASSERT_FALSE(data.GetCanBePlacedAtPosition(x, y, num)) << x << y << num;
                    else
                        ASSERT_TRUE(data.GetCanBePlacedAtPosition(x, y, num)) << x << y << num;
                }
            }
        }
    }
}



TEST(SetUpPossibleSpotsTests, NoPlacedTest)
{
    int sectionSize = 3;
    BoardData data;
    data.SetUpSizes(sectionSize);

    ASSERT_TRUE(data.SetUpPossibleSpots());

    // Everything must be placeable in
    for (int num = 1; num < 10; ++num)
    {
        for (size_t x = 0; x < data.GetBoardSize(); ++x)
        {
            for (size_t y = 0; y < data.GetBoardSize(); ++y)
            {
                ASSERT_TRUE(data.GetCanBePlacedAtPosition(x, y, num));
            }
        }
    }

    for (int num = 1; num < 10; ++num)
    {
        for (size_t sectionX = 0; sectionX < data.GetSectionSize(); ++sectionX)
        {
            for (size_t sectionY = 0; sectionY < data.GetSectionSize(); ++sectionY)
            {
                ASSERT_FALSE(data.GetNumberPlacedInSection(sectionX, sectionY, num));
            }
        }
    }
}




TEST(SetUpPossibleSpotsTests, ValidBoardTest)
{
    BoardData data;

    ASSERT_TRUE(LoadBoard(data, "setUp_valid", "../../Unit Tests/examples.txt"));

    ASSERT_TRUE(data.SetUpPossibleSpots());

    // Check to see if the section was claimed
    ASSERT_TRUE(data.GetNumberPlacedInSection(0, 0, 1));


    for (size_t num = 2; num <= 9; ++num)
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(0, 0, num));

    // Only a single column and single row are changed
    for (size_t pos = 0; pos < 9; ++pos)
    {
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(pos, 0, 1));
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(0, pos, 1));
    }
}



TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Row)
{
    BoardData data;

    ASSERT_TRUE(LoadBoard(data, "invalid_row", "../../Unit Tests/examples.txt"));

    ASSERT_FALSE(data.SetUpPossibleSpots());
}




TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Column)
{
    BoardData data;

    ASSERT_TRUE(LoadBoard(data, "invalid_column", "../../Unit Tests/examples.txt"));

    ASSERT_FALSE(data.SetUpPossibleSpots());
}




TEST(SetUpPossibleSpotsTests, InvalidBoardTest_Section)
{
    BoardData data;

    ASSERT_TRUE(LoadBoard(data, "invalid_section", "../../Unit Tests/examples.txt"));

    ASSERT_FALSE(data.SetUpPossibleSpots());
}



TEST(SetBoxTest, CompleteTest)
{
    BoardData data;
    data.SetUpSizes(3);

    data.SetBox(0, 0, 1);

    // Check to see if the section was claimed, 
    ASSERT_TRUE(data.GetNumberPlacedInSection(0, 0, 1));

    
    for (size_t num = 2; num < data.GetNumberOfPossibleNumbers(); ++num)
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(0, 0, num));
    
    // Only a single column and single row are changed
    for (size_t pos = 0; pos < data.GetBoardSize(); ++pos)
    {
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(pos, 0, 1));
        ASSERT_FALSE(data.GetCanBePlacedAtPosition(0, pos, 1));
    }

    for (size_t x = 1; x < data.GetBoardSize(); ++x)
    {
        for (size_t y = 1; y < data.GetBoardSize(); ++y)
            // This is because for all boxes in the (0, 0) section, they cannot be placed in
            if (x >= data.GetSectionSize() || y >= data.GetSectionSize())
                ASSERT_TRUE(data.GetCanBePlacedAtPosition(x, y, 1));
    }
}