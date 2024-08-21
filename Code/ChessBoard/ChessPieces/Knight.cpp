#include "Knight.h"

Knight::Knight(const sf::IntRect& pieceRect, Piece::PieceColor color, const std::string& cellName)
	: Piece(Configuration::chessPiecesTexture, pieceRect, color, cellName)
{

}

int Knight::GetValue() const
{
	return 3;
}

std::vector<ChessBoardCell*> Knight::getAllowedCellsToMove(ChessBoard& chessboard) 
{
	return std::vector<ChessBoardCell*>();
}
