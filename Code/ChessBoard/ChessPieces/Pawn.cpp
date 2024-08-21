#include "Pawn.h"

Pawn::Pawn(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName) 
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Pawn::GetValue() const
{
	return 1;
}
