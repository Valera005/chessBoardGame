#include "Bishop.h"

Bishop::Bishop(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Bishop::GetValue() const
{
	return 3;
}
