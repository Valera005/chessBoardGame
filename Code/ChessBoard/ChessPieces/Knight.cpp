#include "Knight.h"

Knight::Knight(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Knight::GetValue() const
{
	return 3;
}
