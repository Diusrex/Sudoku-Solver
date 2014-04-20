#include "Board Data.h"
#include "Load Board.h"
#include "Standard Checks.h"
#include "Standard Algorithm.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;

void RunProgram()
{
    BoardInformation::BoardData board;
    std::unique_ptr<Algorithm> usedAlgorithm(new StandardAlgorithm());
    
    // The standard size, is possible for other sizes however
    board.SetUpSizes(3);

    // this is for the original showing of the grid, has no numbers however
    board.PrintOut(true);
    
    // basic intro
    cout << "All unknown numbers are represented by a 0 in the grid." << endl << endl;

    string input;
    string again = "y";

    while (again == "y")
    {
        cout << "Do you want to input a puzzle or use an example? (input or example). Enter exit to exit "; 
        cin >> input;

        if (input == "exit")
            break;

        if (input == "example")
        {
            // This means that the user did not choose a puzzle
            if (!ChooseExampleToLoad(board))
                continue;

            cout << "Board to solve is:\n";
            board.PrintOut(false);
        }

        else if (input == "input")
        {
            BoardInformation::EnterPuzzleFromInput(board);  
        }

        else
        {
            cout << "\nSorry, that input was invalid.\n\n";
            continue;
        }

        

        bool valid = usedAlgorithm->BeginSolving(board);

        if (!valid)
            cout << "The board was not valid\n";


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
        

        cout << "\nDo you want to do solve another puzzle? (y or n) "; cin >> again;

        if (again == "y")
        {
            // Reset the board
            board = BoardInformation::BoardData();
            board.SetUpSizes(3);
        }
    }
}
