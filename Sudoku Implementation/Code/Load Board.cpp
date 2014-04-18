#include "Board Data.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "Load Board.h"

using namespace std;

vector<string> GetAllPossiblePuzzles(string filePath);

bool BoardInformation::ChooseExampleToLoad(BoardData& board)
{
    string examplesPath = "examples.txt";

    vector<string> allOptions = GetAllPossiblePuzzles(examplesPath);

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

        if (LoadBoard(board, input, examplesPath))
        {
            return true;
        }

        cout << "Sorry, that input was not a valid board.\n\n";
    }
}


vector<string> GetAllPossiblePuzzles(string filePath)
{
    ifstream file("examples.txt");

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


bool BoardInformation::LoadBoard(BoardData& board, const std::string& wanted, const std::string& filePath)
{
    ifstream file(filePath);

    vector<string> allOptions;

    if (file.is_open())
    {
        string current;

        while (file >> current)
        {
            if (current == wanted)
            {
                int boxSize;
                file >> boxSize;
                board.SetUp(boxSize);

                for (size_t y = 0; y < board.boardSize; ++y)
                {
                    for (size_t x = 0; x < board.boardSize; ++x)
                    {
                        file >> board.board[x][y];
                    }
                }

                return true;
            }
        }
    }

    return false;
}