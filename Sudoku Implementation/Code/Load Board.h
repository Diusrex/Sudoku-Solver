#pragma once

#include <string>

namespace BoardInformation {

    struct BoardData;

    bool ChooseExampleToLoad(BoardData& board);

    bool LoadBoard(BoardData& board, const std::string& wanted, const std::string& filePath);


}