#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:
	Queen(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Queen(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~Queen() {}
};


