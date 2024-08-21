#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Rook : public Piece
{

public:
	static int value;

	Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Rook() {}

	virtual int GetValue() const;
};

