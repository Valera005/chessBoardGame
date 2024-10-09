#pragma once
#include <string>

class Piece;
class Cell;

class BoardUtils {
public:
    static int CellNameToIndex(const std::string& cellName);
    static std::string IndexToCellName(int index);

    static std::string PieceToString(const Piece& piece);
    static std::string CellToString(const Cell& cell);
};
