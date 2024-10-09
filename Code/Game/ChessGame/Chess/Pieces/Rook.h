#pragma once
#include "Piece.h"

class Rook : public Piece
{

public:
	Rook(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Rook(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~Rook() {}
};

