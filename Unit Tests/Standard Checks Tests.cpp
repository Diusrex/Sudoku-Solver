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

    // This would represent not being able to be placed in top left, and bottom right of top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][1][1] = false;

    // This would represent having claimed the top right box for 2
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[2][0][1] = false;
    board.canBePlacedIn[2][1][1] = false;
    board.canBePlacedIn[2][1][0] = false;
    board.numberPlacedInSection[2][0][0] = true;

    ASSERT_FALSE(IsImpossible(board));
}




TEST(IsImpossibleTests, IsImpossibleTest)
{
    BoardData board;

    board.SetUpSizes(2);

    // This would represent not being able to be placed in top right box
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][0][1] = false;
    board.canBePlacedIn[1][1][0] = false;
    board.canBePlacedIn[1][1][1] = false;
    ASSERT_TRUE(IsImpossible(board));
}




TEST(GetOnlyNumberCanBePlacedTests, OneExists)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[3][0][0] = false;

    ASSERT_EQ(4, GetOnlyNumberCanBePlaced(board, 0, 0));
}



TEST(GetOnlyNumberCanBePlacedTests, MultipleOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}




TEST(GetOnlyNumberCanBePlacedTests, NoOptions)
{
    BoardData board;

    board.SetUpSizes(2);

    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[2][0][0] = false;
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[4][0][0] = false;

    ASSERT_EQ(0, GetOnlyNumberCanBePlaced(board, 0, 0));
}


// This means should not get anything
TEST(GetRowAndColumnOnlyPossibleTests, AllAvailable)
{
    BoardData board;

    board.SetUpSizes(2);

    std::vector<int> rowOnlyPos(board.boardSize + 1), columnOnlyPos(board.boardSize + 1);
    std::vector<bool> singleOccuranceInRow(board.boardSize + 1), singleOccuranceInColumn(board.boardSize + 1);

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    for (size_t num = 1; num <= board.boardSize; ++num)
    {
        ASSERT_FALSE(singleOccuranceInRow[num]);
        ASSERT_FALSE(singleOccuranceInColumn[num]);
    }
}



TEST(GetRowAndColumnOnlyPossibleTests, RowSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);

    // This will mean that the number 1 can only be placed in [3] for the row 0
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][0][1] = false;
    board.canBePlacedIn[1][0][2] = false;

    // This will mean that the number 2 can only be placed in [0] for the row 0
    board.canBePlacedIn[2][0][1] = false;
    board.canBePlacedIn[2][0][2] = false;
    board.canBePlacedIn[2][0][3] = false;

    // This will mean that the number 3 can only be placed in [1] for the row 0
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[3][0][2] = false;
    board.canBePlacedIn[3][0][3] = false;

    std::vector<int> rowOnlyPos(board.boardSize + 1), columnOnlyPos(board.boardSize + 1);
    std::vector<bool> singleOccuranceInRow(board.boardSize + 1), singleOccuranceInColumn(board.boardSize + 1);

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInRow[1]);
    ASSERT_EQ(3, rowOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInRow[2]);
    ASSERT_EQ(0, rowOnlyPos[2]);
    ASSERT_TRUE(singleOccuranceInRow[3]);
    ASSERT_EQ(1, rowOnlyPos[3]);

}



TEST(GetRowAndColumnOnlyPossibleTests, ColumnSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);

    // This will mean that the number 1 can only be placed in [3] for the column 0
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][1][0] = false;
    board.canBePlacedIn[1][2][0] = false;

    // This will mean that the number 2 can only be placed in [0] for the column 0
    board.canBePlacedIn[2][1][0] = false;
    board.canBePlacedIn[2][2][0] = false;
    board.canBePlacedIn[2][3][0] = false;

    // This will mean that the number 3 can only be placed in [1] for the column 0
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[3][2][0] = false;
    board.canBePlacedIn[3][3][0] = false;

    std::vector<int> rowOnlyPos(board.boardSize + 1), columnOnlyPos(board.boardSize + 1);
    std::vector<bool> singleOccuranceInRow(board.boardSize + 1), singleOccuranceInColumn(board.boardSize + 1);

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInColumn[1]);
    ASSERT_EQ(3, columnOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInColumn[2]);
    ASSERT_EQ(0, columnOnlyPos[2]);
    ASSERT_TRUE(singleOccuranceInColumn[3]);
    ASSERT_EQ(1, columnOnlyPos[3]);

}




TEST(GetRowAndColumnOnlyPossibleTests, RowAndColumnSingleAvailableTests)
{
    BoardData board;

    board.SetUpSizes(2);

    // This will mean that the number 1 can only be placed in [3] for the row 0
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][0][1] = false;
    board.canBePlacedIn[1][0][2] = false;

    // This will mean that the number 1 can only be placed in [3] for the column 0
    board.canBePlacedIn[1][0][0] = false;
    board.canBePlacedIn[1][1][0] = false;
    board.canBePlacedIn[1][2][0] = false;


    // This will mean that the number 2 can only be placed in [0] for the row 0
    board.canBePlacedIn[2][0][1] = false;
    board.canBePlacedIn[2][0][2] = false;
    board.canBePlacedIn[2][0][3] = false;

    // This will mean that the number 2 can only be placed in [0] for the column 0
    board.canBePlacedIn[2][1][0] = false;
    board.canBePlacedIn[2][2][0] = false;
    board.canBePlacedIn[2][3][0] = false;


    // This will mean that the number 3 can only be placed in [1] for the row 0
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[3][0][2] = false;
    board.canBePlacedIn[3][0][3] = false;

    // This will mean that the number 3 can only be placed in [1] for the column 0
    board.canBePlacedIn[3][0][0] = false;
    board.canBePlacedIn[3][2][0] = false;
    board.canBePlacedIn[3][3][0] = false;

    std::vector<int> rowOnlyPos(board.boardSize + 1), columnOnlyPos(board.boardSize + 1);
    std::vector<bool> singleOccuranceInRow(board.boardSize + 1), singleOccuranceInColumn(board.boardSize + 1);

    GetRowAndColumnOnlyPossible(board, 0, rowOnlyPos, singleOccuranceInRow, columnOnlyPos, singleOccuranceInColumn);

    ASSERT_TRUE(singleOccuranceInRow[1]);
    ASSERT_EQ(3, rowOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInRow[2]);
    ASSERT_EQ(0, rowOnlyPos[2]);
    ASSERT_TRUE(singleOccuranceInRow[3]);
    ASSERT_EQ(1, rowOnlyPos[3]);

    ASSERT_TRUE(singleOccuranceInColumn[1]);
    ASSERT_EQ(3, columnOnlyPos[1]);
    ASSERT_TRUE(singleOccuranceInColumn[2]);
    ASSERT_EQ(0, columnOnlyPos[2]);
    ASSERT_TRUE(singleOccuranceInColumn[3]);
    ASSERT_EQ(1, columnOnlyPos[3]);
}


TEST(GetSectionOnlyPossibleTests, MultipleAvailableTest)
{
    BoardData board;

    board.SetUpSizes(2);

    std::vector<std::pair<size_t, size_t>> positionInSection(board.boardSize + 1); 
    std::vector<bool> singleOccuranceInSection(board.boardSize + 1);

    GetSectionOnlyPossible(board, 0, 0, positionInSection, singleOccuranceInSection);

    for (size_t num = 1; num <= board.boardSize; ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]);
}



TEST(GetSectionOnlyPossibleTests, SingleSpotTest)
{
    BoardData board;

    // If either of these are false, then no poin in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section", "../../Unit Tests/examples.txt"));
    ASSERT_TRUE(SetUpPossibleSpots(board));

    std::vector<std::pair<size_t, size_t>> positionInSection(board.boardSize + 1);
    std::vector<bool> singleOccuranceInSection(board.boardSize + 1);

    GetSectionOnlyPossible(board, 0, 0, positionInSection, singleOccuranceInSection);

    ASSERT_TRUE(singleOccuranceInSection[1]);
    ASSERT_EQ(0, positionInSection[1].first); ASSERT_EQ(0, positionInSection[1].second);

    ASSERT_TRUE(singleOccuranceInSection[2]);
    ASSERT_EQ(2, positionInSection[2].first); ASSERT_EQ(2, positionInSection[2].second);

    ASSERT_TRUE(singleOccuranceInSection[3]);
    ASSERT_EQ(2, positionInSection[3].first); ASSERT_EQ(0, positionInSection[3].second);

    for (size_t num = 4; num <= board.boardSize; ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]) << num;
}



TEST(GetSectionOnlyPossibleTests, OffsetTest)
{
    BoardData board;

    // If either of these are false, then no poin in continuing
    ASSERT_TRUE(LoadBoard(board, "unsolved_section_offset", "../../Unit Tests/examples.txt"));
    ASSERT_TRUE(SetUpPossibleSpots(board));

    std::vector<std::pair<size_t, size_t>> positionInSection(board.boardSize + 1);
    std::vector<bool> singleOccuranceInSection(board.boardSize + 1);

    GetSectionOnlyPossible(board, 1, 1, positionInSection, singleOccuranceInSection);

    ASSERT_TRUE(singleOccuranceInSection[1]);
    ASSERT_EQ(2, positionInSection[1].first); ASSERT_EQ(2, positionInSection[1].second);

    ASSERT_TRUE(singleOccuranceInSection[2]);
    ASSERT_EQ(0, positionInSection[2].first); ASSERT_EQ(2, positionInSection[2].second);

    ASSERT_TRUE(singleOccuranceInSection[3]);
    ASSERT_EQ(0, positionInSection[3].first); ASSERT_EQ(1, positionInSection[3].second);

    for (size_t num = 4; num <= board.boardSize; ++num)
        ASSERT_FALSE(singleOccuranceInSection[num]) << num;
}