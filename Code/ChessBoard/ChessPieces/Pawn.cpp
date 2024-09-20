#include "Pawn.h"
#include "..\ChessBoard.h"

Pawn::Pawn(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName, const GetAllowedCellsFuncType& GetAllowedCells)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName, GetAllowedCells, Piece::PieceType::Pawn)
{

}

int Pawn::GetValue() const
{
	return 1;
}

