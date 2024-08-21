#include "King.h"

King::King(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int King::GetValue() const
{
	return 0;
}
