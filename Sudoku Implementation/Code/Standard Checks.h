#pragma once

namespace BoardInformation {

    struct BoardData;

    bool IsSolved(const BoardData& board);

    bool IsImpossible(const BoardData & board);
}