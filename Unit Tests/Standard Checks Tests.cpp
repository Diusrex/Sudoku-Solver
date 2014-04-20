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
    
    // The following code is possible because 2 is in the board, and it doesn't matter than 1 is missing 2 spots

    // This would represent having placed 2 in the top left section
    board.SetBox(0, 1, 2);

    // This would represent not being able to only be able to place 1 in a single box within the top right section
    board.SetBox(1, 1, 3);
    board.SetBox(1, 0, 4);

    ASSERT_FALSE(IsImpossible(board));
}




TEST(IsImpossibleTests, IsImpossibleTest)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would make it so that 1 can only be placed in the bottom left corner of the top section
    board.SetBox(2, 0, 1);
    board.SetBox(0, 2, 1);

    // This would make placing 1 in the top section be impossible
    board.SetBox(1, 1, 2);

    ASSERT_TRUE(IsImpossible(board));
}




TEST(GetOnlyNumberCanBePlacedTests, OneExists)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would case (0, 0) be the only possible spot for 4 in the top left section
    board.SetBox(1, 0, 1);
    board.SetBox(0, 1, 2);
    board.SetBox(1, 1, 3);

    ASSERT_EQ(4, GetOnlyNumberCanBePlaced(board, 0, 0));
}



TEST(GetOnlyNumberCanBePlacedTests, MultipleOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would mean that there are two number that can be placed into (0, 0)
    board.SetBox(1, 0, 1);
    board.SetBox(0, 1, 2);

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}




TEST(GetOnlyNumberCanBePlacedTests, NoOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would represent having no possible number be able to be placed in (0, 0)
    board.SetBox(0, 0, 1);

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}


// This means should not get anything
TEST(GetRowAndColumnOnlyPossibleTests, AllAvailable)
{
    BoardData board;

    board.SetUpSizes(2);

    std::vector<int> rowOnlyPos(board.GetNumberOfPossibleNumbers()), columnOnlyPos(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInRow(board.GetNumberOfPossibleNumbers()), singleOccuranceInColumn(board.GetNumberOfPossibleNumbers());

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
    {
        ASSERT_FALSE(singleOccuranceInRow[num]);
        ASSERT_FALSE(singleOccuranceInColumn[num]);
    }
}


// There is no need to test for if a spot has already been taken in the row, because then everything will be false
TEST(GetRowAndColumnOnlyPossibleTests, RowSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);

    // This will mean that the number 1 can only be placed in [3] for the row 0
    board.SetBox(0, 1, 1);
    board.SetBox(2, 2, 1);

    std::vector<int> rowOnlyPos(board.GetNumberOfPossibleNumbers()), columnOnlyPos(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInRow(board.GetNumberOfPossibleNumbers()), singleOccuranceInColumn(board.GetNumberOfPossibleNumbers());

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInRow[1]);
    ASSERT_EQ(3, rowOnlyPos[1]);
}





TEST(GetRowAndColumnOnlyPossibleTests, ColumnSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);
    
    // This will mean that the number 1 can only be placed in [3] for the column 0
        // First sets the [0] and [1] to false. Second sets [2] to false
    board.SetBox(1, 0, 1);
    board.SetBox(2, 2, 1);
    
    
    std::vector<int> rowOnlyPos(board.GetNumberOfPossibleNumbers()), columnOnlyPos(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInRow(board.GetNumberOfPossibleNumbers()), singleOccuranceInColumn(board.GetNumberOfPossibleNumbers());

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInColumn[1]);
    ASSERT_EQ(3, columnOnlyPos[1]);
}




TEST(GetRowAndColumnOnlyPossibleTests, RowAndColumnSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);

    // This will mean that the number 1 can only be placed in [2] for the row 0, and in the [3] for column 0
    board.SetBox(1, 1, 1);
    board.SetBox(3, 2, 1);


    // This will mean that the number 2 can only be placed in [0] for the row 0, and in [0] for column 0
    board.SetBox(2, 1, 2);
    board.SetBox(1, 2, 2);

    std::vector<int> rowOnlyPos(board.GetNumberOfPossibleNumbers()), columnOnlyPos(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInRow(board.GetNumberOfPossibleNumbers()), singleOccuranceInColumn(board.GetNumberOfPossibleNumbers());

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInRow[1]);
    ASSERT_EQ(2, rowOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInRow[2]);
    ASSERT_EQ(0, rowOnlyPos[2]);

    ASSERT_TRUE(singleOccuranceInColumn[1]);
    ASSERT_EQ(3, columnOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInColumn[2]);
    ASSERT_EQ(0, columnOnlyPos[2]);
}


TEST(GetSectionOnlyPossibleTests, MultipleAvailableTest)
{
    BoardData board;

    board.SetUpSizes(2);

    std::vector<std::pair<size_t, size_t>> positionInSection(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInSection(board.GetNumberOfPossibleNumbers());

    GetSectionOnlyPossible(board, 0, 0, positionInSection, singleOccuranceInSection);

    for (size_t num = 1; num < board.GetNumberOfPossibleNumbers(); ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]);
}



TEST(GetSectionOnlyPossibleTests, SingleSpotTest)
{
    BoardData board;

    // If either of these are false, then no point in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section", "../../Unit Tests/examples.txt"));
    ASSERT_TRUE(board.SetUpPossibleSpots());

    std::vector<std::pair<size_t, size_t>> positionInSection(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInSection(board.GetNumberOfPossibleNumbers());

    GetSectionOnlyPossible(board, 0, 0, positionInSection, singleOccuranceInSection);

    ASSERT_TRUE(singleOccuranceInSection[1]);
    ASSERT_EQ(0, positionInSection[1].first); ASSERT_EQ(0, positionInSection[1].second);

    ASSERT_TRUE(singleOccuranceInSection[2]);
    ASSERT_EQ(2, positionInSection[2].first); ASSERT_EQ(2, positionInSection[2].second);

    ASSERT_TRUE(singleOccuranceInSection[3]);
    ASSERT_EQ(2, positionInSection[3].first); ASSERT_EQ(0, positionInSection[3].second);

    for (size_t num = 4; num < board.GetNumberOfPossibleNumbers(); ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]) << num;
}



TEST(GetSectionOnlyPossibleTests, OffsetTest)
{
    BoardData board;

    // If either of these are false, then no point in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section_offset", "../../Unit Tests/examples.txt"));
    ASSERT_TRUE(board.SetUpPossibleSpots());

    std::vector<std::pair<size_t, size_t>> positionInSection(board.GetNumberOfPossibleNumbers());
    std::vector<bool> singleOccuranceInSection(board.GetNumberOfPossibleNumbers());

    GetSectionOnlyPossible(board, 1, 1, positionInSection, singleOccuranceInSection);

    ASSERT_TRUE(singleOccuranceInSection[1]);
    ASSERT_EQ(2, positionInSection[1].first); ASSERT_EQ(2, positionInSection[1].second);

    ASSERT_TRUE(singleOccuranceInSection[2]);
    ASSERT_EQ(0, positionInSection[2].first); ASSERT_EQ(2, positionInSection[2].second);

    ASSERT_TRUE(singleOccuranceInSection[3]);
    ASSERT_EQ(0, positionInSection[3].first); ASSERT_EQ(1, positionInSection[3].second);

    for (size_t num = 4; num < board.GetNumberOfPossibleNumbers(); ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]) << num;
}