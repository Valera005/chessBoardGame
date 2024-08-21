#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class King : public Piece
{

public:

	King(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~King() {}

	virtual int GetValue() const;

	virtual std::vector<ChessBoardCell*> getAllowedCellsToMove(ChessBoard& chessboard) ;
};

