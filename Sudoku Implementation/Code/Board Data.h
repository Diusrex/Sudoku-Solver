#pragma once

#include <vector>

#include "gtest/gtest_prod.h"

namespace BoardInformation {


    class BoardData {
    public:
        size_t GetNumberAtPosition(size_t x, size_t y) const { return board[x][y]; }
        bool GetCanBePlacedAtPosition(size_t x, size_t y, size_t num) const { return canBePlacedIn[num][x][y]; }

        bool GetNumberPlacedInSection(size_t sectionX, size_t sectionY, size_t num) const { return numberPlacedInSection[num][sectionX][sectionY]; }

        size_t GetBoardSize() const { return boardSize; }
        size_t GetSectionSize() const { return sectionSize; }
        size_t GetNumberOfSections() const { return sectionSize; }

        // Will be the boardSize + 1, so that it can be < rather than <=
        size_t GetNumberOfPossibleNumbers() const { return boardSize + 1; }
        void SetUpSizes(size_t boxSize);

        // Will set up canBePlacedIn and numberPlacedInBox
        // Note, should not be called when the board is changed, only when it is loaded
        bool SetUpPossibleSpots();

        // Will nicely print out the array
        void PrintOut() const;

        void SetBox(const size_t x, const size_t y, const size_t takenNum);

        // This is not a member because it is does not belong with the rest of board data's members
        friend bool LoadBoard(BoardData& board, const std::string& wanted, const std::string& filePath);

    private:
        // Will update the vertical and horizontal availability of the given number, as well as it's availability in the section
        void UpdatePossibleSpots(const size_t x, const size_t y, const size_t takenNum);
        
        // [x][y]
        std::vector<std::vector<int>> board;

        // Will store if a specific position can be placed in [num][x][y]
        std::vector<std::vector<std::vector<bool>>> canBePlacedIn;

        // Will store if the number is in each box. Will be [num][sectionX][sectionY]
        std::vector<std::vector<std::vector<bool>>> numberPlacedInSection;

        // boardSize is also the highest number that can be placed
        size_t boardSize, sectionSize;

        FRIEND_TEST(BoardDataTest, ProperCreationSize);
    };

    // Works for both x and y the same way
    size_t ConvertFromPositionToSection(const BoardData& board, size_t pos);

    // Works for both x and y
    size_t ConvertFromPositionToSectionOffset(const BoardData& board, size_t pos);

    // Works for both x and y
    size_t ConvertFromSectionToSectionOffset(const BoardData& board, size_t sectionPos);
}