#pragma once
#include <memory>
#include <vector>
#include "../Pieces/Piece.h"
#include "../Board.h"

//class Board;
//enum class Board::MoveExecutionStatus;
class Move;

class MoveValidator
{
	
public:

	static Board::MoveExecutionStatus isValidMove(Move& move, const Board& board);
	static std::vector<std::shared_ptr<Move>> filterValidMoves(const std::vector<std::shared_ptr<Move>>& moves, const Board& board);
	static bool IsKingInCheck(Piece::PieceColor kingColor, const Board& board);

};

