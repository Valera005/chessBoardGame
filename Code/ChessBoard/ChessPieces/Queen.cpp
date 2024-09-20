#include "Queen.h"

Queen::Queen(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::Queen)
{

}

int Queen::GetValue() const
{
	return 9;
}

