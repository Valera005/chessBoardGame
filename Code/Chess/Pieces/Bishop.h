#pragma once
#include "Piece.h"

class Bishop : public Piece
{

public:
	Bishop(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Bishop(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~Bishop() {}
};

