#include "Pawn.h"
#include "..\ChessBoard.h"

Pawn::Pawn(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName) 
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Pawn::GetValue() const
{
	return 1;
}

std::vector<ChessBoardCell*> Pawn::getAllowedCellsToMove(ChessBoard& chessboard)
{
	std::vector<ChessBoardCell*> answer{};

	int index = chessboard.CellNameToIndex(this->cellName);

	if (this->color == PieceColor::White)
	{
		answer.push_back(&chessboard[index + 8]);
	}
	else
	{
		answer.push_back(&chessboard[index - 8]);
	}

	return std::vector<ChessBoardCell*>();
}
