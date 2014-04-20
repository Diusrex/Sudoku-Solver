
#include <iostream>

#include "..\Sudoku Implementation\Code\Board Data.h"
#include "..\Sudoku Implementation\Code\Standard Checks.h"
#include "..\Sudoku Implementation\Code\Standard Algorithm.h"

#include <memory>
#include <iostream>
#include <string>

bool GetExample(BoardInformation::BoardData& board);

using namespace std;

int main()
{
    BoardInformation::BoardData board;
    std::unique_ptr<Algorithm> usedAlgorithm(new StandardAlgorithm());


    for (;;)
    {
        cout << "Do you want to load the puzzle from example (e) or from input (i)? Enter q to exit\n";
        
        string input;
        cin >> input;

        if (input == "q")
            break;

        
        if (input == "e")
        {
            if (GetExample(board))
            {
                cout << "Board to solve is:\n";
                board.PrintOut();

                bool valid = usedAlgorithm->BeginSolving(board);

                if (!valid)
                {
                    cout << "The board was not valid\n";
                }

                else if (BoardInformation::IsSolved(board))
                {
                    cout << "The completed board looks like:\n";
                    board.PrintOut();
                }

                else
                {
                    cout << "The board was unable to be completed\n";
                    board.PrintOut();
                }
            }

            else if (input == "i")
            {
            }
        }
    }

	return 0;
}

