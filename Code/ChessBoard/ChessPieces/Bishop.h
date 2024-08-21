#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Bishop : public Piece
{

public:

	Bishop(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Bishop() {}

	virtual int GetValue() const;

	virtual std::vector<ChessBoardCell*> getAllowedCellsToMove(ChessBoard& chessboard) ;
};

