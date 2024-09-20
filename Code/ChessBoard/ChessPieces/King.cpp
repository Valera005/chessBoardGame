#include "King.h"

King::King(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::King)
{

}

int King::GetValue() const
{
	return 0;
}
