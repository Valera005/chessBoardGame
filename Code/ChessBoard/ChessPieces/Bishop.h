#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Bishop : public Piece
{

public:
	static int value;

	Bishop(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Bishop() {}

	virtual int GetValue() const;
};

