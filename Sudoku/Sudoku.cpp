
#include <iostream>

#include "..\Sudoku Implementation\Code\Board Data.h"

int main()
{
    BoardData data;
    data.SetUp(3);
    data.PrintOut();

    int temp;
    std::cin >> temp;
	return 0;
}
