#pragma once
#include "Piece.h"

class Knight : public Piece
{

public:
	Knight(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Knight(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~Knight() {}
};
