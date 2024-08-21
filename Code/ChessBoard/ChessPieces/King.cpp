#include "King.h"

King::King(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int King::GetValue() const
{
	return 0;
}

std::vector<ChessBoardCell*> King::getAllowedCellsToMove(ChessBoard& chessboard) 
{
	return std::vector<ChessBoardCell*>();
}
