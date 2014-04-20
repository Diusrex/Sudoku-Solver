#include "..\Sudoku Implementation\Code\Board Data.h"
#include "..\Sudoku Implementation\Code\Load Board.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> GetAllPossiblePuzzles(const std::string& filePath);

// Will return true if it loaded a board, otherwise will return false
bool GetExample(BoardInformation::BoardData& board)
{
    std::string filePath = "examples.txt";

    std::vector<string> allOptions = GetAllPossiblePuzzles(filePath);

    if (allOptions.size() == 0)
    {
        cout << "\nUnfortunately, there are no available saved puzzles.\n\n";
        return false;
    }

    for (;;)
    {
        cout << "What example do you want to load? Enter q to quit. All possible puzzles are: \n";


        for (size_t i = 0; i < allOptions.size(); ++i)
        {
            // For nice formatting
            if (i != 0)
            {
                cout << ", ";

                if (i + 1 == allOptions.size())
                    cout << "and ";
            }

            cout << allOptions[i];
        }

        cout << ".\n";

        string input;

        cin >> input;

        if (input == "q")
            return false;

        if (BoardInformation::LoadBoard(board, input, filePath))
            return true;
        

        cout << "Sorry, that input was invalid\n\n";
    }
}


vector<string> GetAllPossiblePuzzles(const std::string& filePath)
{
    ifstream file(filePath);

    vector<string> allOptions;

    if (file.is_open())
    {
        string temp;

        while (file >> temp)
        {
            if (temp == "puzzle:")
            {
                file >> temp;
                allOptions.push_back(temp);
            }
        }
    }

    return allOptions;
}