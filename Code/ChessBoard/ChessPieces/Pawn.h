#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"


class Pawn : public Piece
{
public:

	Pawn(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Pawn() {}

	virtual int GetValue() const;

	virtual std::vector<ChessBoardCell*> getAllowedCellsToMove(ChessBoard& chessboard);
};

