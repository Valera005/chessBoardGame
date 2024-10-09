#include "Bishop.h"
#include "../Board.h"
#include "../Cell/Cell.h"

Bishop::Bishop(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : Piece(pieceColor, pieceType, value, cellIndex)
{
}

Bishop::Bishop(const Piece& other) : Piece(other)
{

}

std::vector<std::shared_ptr<Move>> Bishop::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{};

	const Cell* cell = &(chessboard[this->cellIndex]);
	int row = this->cellIndex / Board::row_width;
	int column = this->cellIndex % Board::col_height;

	int index = this->cellIndex;
	int checkIndex = 0;

	int row_temp = row + 1, col_temp = column + 1;

	// we go up right
	while (row_temp <= 7 && col_temp <= 7 && !chessboard[row_temp * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		
		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		row_temp++;
		col_temp++;
	}

	row_temp = row + 1, col_temp = column - 1;
	// up left
	while (row_temp <= 7 && col_temp >= 0 && !chessboard[row_temp * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		
		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		row_temp++;
		col_temp--;
	}

	row_temp = row - 1, col_temp = column - 1;
	// down left
	while (row_temp >= 0 && col_temp >= 0 && !chessboard[row_temp * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		
		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		row_temp--;
		col_temp--;
	}

	row_temp = row - 1, col_temp = column + 1;
	// down right
	while (row_temp >= 0 && col_temp <= 7 && !chessboard[row_temp * 8 + col_temp].IsThereFriendPiece(this->color))
	{
		checkIndex = row_temp * 8 + col_temp;
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		
		if (chessboard[checkIndex].IsThereEnemyPiece(this->color)) break;
		row_temp--;
		col_temp++;
	}


	return answer;
}
