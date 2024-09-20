#include "Rook.h"
#include "..\ChessBoard.h"

Rook::Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells) : 
	Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::Rook)
{

}

int Rook::GetValue() const
{
	return 5;
}

