#include "Rook.h"
#include "../Board.h"
#include "../Cell/Cell.h"

Rook::Rook(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : Piece(pieceColor, pieceType, value, cellIndex)
{

}

Rook::Rook(const Piece& other): Piece(other)
{

}

std::vector<std::shared_ptr<Move>> Rook::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{};

	const Cell* cell = &(chessboard[this->cellIndex]);
	int row = this->cellIndex / Board::row_width;
	int column = this->cellIndex % Board::col_height;

	int index = this->cellIndex;
	int checkIndex = 0;

	int row_temp = row - 1, col_temp = column;

	// we go down
	while (row_temp >= 0 && !chessboard[row_temp * 8 + column].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + column;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break; // try delete it
		row_temp--;
	}

	// go up
	row_temp = row + 1;
	while (row_temp <= 7 && !chessboard[row_temp * 8 + column].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + column;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		row_temp++;
	}

	// go left
	col_temp = column - 1;
	while (col_temp >= 0 && !chessboard[row * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		col_temp--;
	}


	// go right
	col_temp = column + 1;
	while (col_temp <= 7 && !chessboard[row * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		col_temp++;
	}

	return answer;
}
