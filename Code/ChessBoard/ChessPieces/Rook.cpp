#include "Rook.h"


Rook::Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName) : Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Rook::GetValue() const
{
	return 5;
}
