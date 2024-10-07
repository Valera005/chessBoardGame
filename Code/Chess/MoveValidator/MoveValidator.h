#pragma once
#include <memory>
#include <vector>
#include "../Pieces/Piece.h"

class Board;
class Move;
//class Piece;
//enum class Piece::PieceColor;

class MoveValidator
{
	
public:

	static bool isValidMove(const Move& move, const Board& board);
	static std::vector<std::shared_ptr<Move>> filterValidMoves(const std::vector<std::shared_ptr<Move>>& moves, const Board& board);
	static bool IsKingInCheck(Piece::PieceColor kingColor, const Board& board);

};

