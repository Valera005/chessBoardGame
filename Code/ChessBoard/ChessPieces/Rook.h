#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Rook : public Piece
{

public:

	Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName,
		const GetAllowedCellsFuncType& GetAllowedCells);
	virtual ~Rook() {}

	virtual int GetValue() const;

};

