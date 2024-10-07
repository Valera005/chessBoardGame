#pragma once
#include <string>
class BoardUtils {
public:
    static int CellNameToIndex(const std::string& cellName);
    static std::string IndexToCellName(int index);
};
