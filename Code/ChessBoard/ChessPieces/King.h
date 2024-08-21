#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class King : public Piece
{

public:
	static int value;

	King(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~King() {}

	virtual int GetValue() const;
};

