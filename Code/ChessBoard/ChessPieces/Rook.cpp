#include "Rook.h"
#include "..\ChessBoard.h"

Rook::Rook(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName) : Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Rook::GetValue() const
{
	return 5;
}

std::vector<ChessBoardCell*> Rook::getAllowedCellsToMove(ChessBoard& chessboard) 
{
	std::vector<ChessBoardCell*> answer{};
	

	answer.push_back(&chessboard["a2"]);
	

	return answer;
}
