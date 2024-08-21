#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Queen : public Piece
{

public:
	static int value;

	Queen(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Queen() {}

	virtual int GetValue() const;
};


