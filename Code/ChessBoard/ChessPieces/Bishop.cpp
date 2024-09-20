#include "Bishop.h"

Bishop::Bishop(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::Bishop)
{

}

int Bishop::GetValue() const
{
	return 3;
}

