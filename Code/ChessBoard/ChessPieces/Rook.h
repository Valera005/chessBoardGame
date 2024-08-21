#pragma once
#include "Piece.h"
#include "..\..\Configuration\Configuration.h"

class Rook : public Piece
{

public:

	Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName);
	virtual ~Rook() {}

	virtual int GetValue() const;

	virtual std::vector<ChessBoardCell*> getAllowedCellsToMove(ChessBoard& chessboard) ;
};

