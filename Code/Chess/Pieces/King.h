#pragma once
#include "Piece.h"

class King : public Piece
{

public:
	King(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	King(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~King() {}
};

