#include "Knight.h"

Knight::Knight(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::Knight)
{

}

int Knight::GetValue() const
{
	return 3;
}
