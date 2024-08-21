#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"


class Pawn : public Piece
{
public:
	static int value;

	Pawn(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Pawn() {}

	virtual int GetValue() const;
};

