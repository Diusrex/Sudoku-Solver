#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"

using namespace BoardInformation;

TEST(ConversionTests, ConvertFromPositionToSectionTest)
{
    BoardData data;
    data.SetUpSizes(2);

    ASSERT_EQ(0, ConvertFromPositionToSection(data, 0));
    ASSERT_EQ(0, ConvertFromPositionToSection(data, 1));

    ASSERT_EQ(1, ConvertFromPositionToSection(data, 2));
    ASSERT_EQ(1, ConvertFromPositionToSection(data, 3));

    data.SetUpSizes(3);

    ASSERT_EQ(0, ConvertFromPositionToSection(data, 0));
    ASSERT_EQ(0, ConvertFromPositionToSection(data, 1));
    ASSERT_EQ(0, ConvertFromPositionToSection(data, 2));

    ASSERT_EQ(1, ConvertFromPositionToSection(data, 3));
    ASSERT_EQ(1, ConvertFromPositionToSection(data, 4));
    ASSERT_EQ(1, ConvertFromPositionToSection(data, 5));

    ASSERT_EQ(2, ConvertFromPositionToSection(data, 6));
    ASSERT_EQ(2, ConvertFromPositionToSection(data, 7));
    ASSERT_EQ(2, ConvertFromPositionToSection(data, 8));
}



TEST(ConversionTests, ConvertFromPositionToSectionOffsetTest)
{
    BoardData data;
    data.SetUpSizes(2);

    ASSERT_EQ(0, ConvertFromPositionToSectionOffset(data, 0));
    ASSERT_EQ(0, ConvertFromPositionToSectionOffset(data, 1));

    ASSERT_EQ(2, ConvertFromPositionToSectionOffset(data, 2));
    ASSERT_EQ(2, ConvertFromPositionToSectionOffset(data, 3));

    data.SetUpSizes(3);

    ASSERT_EQ(0, ConvertFromPositionToSectionOffset(data, 0));
    ASSERT_EQ(0, ConvertFromPositionToSectionOffset(data, 1));
    ASSERT_EQ(0, ConvertFromPositionToSectionOffset(data, 2));

    ASSERT_EQ(3, ConvertFromPositionToSectionOffset(data, 3));
    ASSERT_EQ(3, ConvertFromPositionToSectionOffset(data, 4));
    ASSERT_EQ(3, ConvertFromPositionToSectionOffset(data, 5));

    ASSERT_EQ(6, ConvertFromPositionToSectionOffset(data, 6));
    ASSERT_EQ(6, ConvertFromPositionToSectionOffset(data, 7));
    ASSERT_EQ(6, ConvertFromPositionToSectionOffset(data, 8));
}


TEST(ConversionTests, ConvertFromSectionToSectionOffsetTest)
{
    BoardData data;
    data.SetUpSizes(2);

    ASSERT_EQ(0, ConvertFromSectionToSectionOffset(data, 0));

    ASSERT_EQ(2, ConvertFromSectionToSectionOffset(data, 1));

    data.SetUpSizes(3);

    ASSERT_EQ(0, ConvertFromSectionToSectionOffset(data, 0));

    ASSERT_EQ(3, ConvertFromSectionToSectionOffset(data, 1));

    ASSERT_EQ(6, ConvertFromSectionToSectionOffset(data, 2));
}