#include "stdafx.h"

#include "../Sudoku Implementation/Code/Board Data.h"
#include "../Sudoku Implementation/Code/Base Algorithm.h"
#include "../Sudoku Implementation/Code/Load Board.h"


// Is designed to allow testing of the base algorithm functionality
class AlgorithmTester : public Algorithm
{
private:
    void Solve(BoardInformation::BoardData & board)
    {
        GuessSpot(board);
    }
};




TEST(BaseAlgorithmTests, ValidDeterminationTest)
{
    BoardInformation::BoardData data;
    AlgorithmTester tester;
   
    ASSERT_TRUE(BoardInformation::LoadBoard(data, "invalid_row", "../../Unit Tests/examples.txt"));
    
    ASSERT_FALSE(tester.BeginSolving(data));

    ASSERT_TRUE(BoardInformation::LoadBoard(data, "invalid_column", "../../Unit Tests/examples.txt"));

    ASSERT_FALSE(tester.BeginSolving(data));

    ASSERT_TRUE(BoardInformation::LoadBoard(data, "invalid_section", "../../Unit Tests/examples.txt"));

    ASSERT_FALSE(tester.BeginSolving(data));
}



TEST(BaseAlgorithmTests, GuessTester1)
{
    BoardInformation::BoardData data;

    ASSERT_TRUE(BoardInformation::LoadBoard(data, "unsolved_diagonal", "../../Unit Tests/examples.txt"));

    BoardInformation::BoardData dataCopy = data;
    AlgorithmTester tester;
    ASSERT_TRUE(tester.BeginSolving(data));

    // Make sure rest of data wasn't changed, that only the unknown were changed
    for (int x = 0; x < 9; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            // The line where it was unknown
            if (x != y)
                ASSERT_EQ(dataCopy.GetNumberAtPosition(x, y), data.GetNumberAtPosition(x, y));
        }
    }

    ASSERT_EQ(1, data.GetNumberAtPosition(0, 0));
    ASSERT_EQ(5, data.GetNumberAtPosition(1, 1));
    ASSERT_EQ(9, data.GetNumberAtPosition(2, 2));
    ASSERT_EQ(5, data.GetNumberAtPosition(3, 3));
    ASSERT_EQ(9, data.GetNumberAtPosition(4, 4));
    ASSERT_EQ(4, data.GetNumberAtPosition(5, 5));
    ASSERT_EQ(9, data.GetNumberAtPosition(6, 6));
    ASSERT_EQ(4, data.GetNumberAtPosition(7, 7));
    ASSERT_EQ(8, data.GetNumberAtPosition(8, 8));
}


// This is a more difficult version of #1, but there is only 1 possible answer
TEST(BaseAlgorithmTests, GuessTester2)
{
    BoardInformation::BoardData data;

    ASSERT_TRUE(BoardInformation::LoadBoard(data, "unsolved_doubleDiagonal", "../../Unit Tests/examples.txt"));

    AlgorithmTester tester;
    ASSERT_TRUE(tester.BeginSolving(data));

    ASSERT_EQ(1, data.GetNumberAtPosition(0, 0));
    ASSERT_EQ(5, data.GetNumberAtPosition(1, 1));
    ASSERT_EQ(9, data.GetNumberAtPosition(2, 2));
    ASSERT_EQ(5, data.GetNumberAtPosition(3, 3));
    ASSERT_EQ(9, data.GetNumberAtPosition(4, 4));
    ASSERT_EQ(4, data.GetNumberAtPosition(5, 5));
    ASSERT_EQ(9, data.GetNumberAtPosition(6, 6));
    ASSERT_EQ(4, data.GetNumberAtPosition(7, 7));
    ASSERT_EQ(8, data.GetNumberAtPosition(8, 8));

    ASSERT_EQ(9, data.GetNumberAtPosition(8, 0));
    ASSERT_EQ(2, data.GetNumberAtPosition(7, 1));
    ASSERT_EQ(4, data.GetNumberAtPosition(6, 2));
    ASSERT_EQ(7, data.GetNumberAtPosition(5, 3));
    ASSERT_EQ(9, data.GetNumberAtPosition(4, 4));
    ASSERT_EQ(2, data.GetNumberAtPosition(3, 5));
    ASSERT_EQ(5, data.GetNumberAtPosition(2, 6));
    ASSERT_EQ(7, data.GetNumberAtPosition(1, 7));
    ASSERT_EQ(9, data.GetNumberAtPosition(0, 8));
}