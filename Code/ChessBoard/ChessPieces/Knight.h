#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Knight : public Piece
{

public:
	static int value;

	Knight(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Knight() {}

	virtual int GetValue() const;
};
