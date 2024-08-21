#include "Queen.h"

Queen::Queen(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName) : Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Queen::GetValue() const
{
	return 9;
}

std::vector<ChessBoardCell*> Queen::getAllowedCellsToMove(ChessBoard& chessboard) 
{
	return std::vector<ChessBoardCell*>();
}
