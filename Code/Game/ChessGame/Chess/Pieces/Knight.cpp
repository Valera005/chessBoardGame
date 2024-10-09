#include "Knight.h"
#include "../Board.h"
#include "../Cell/Cell.h"

Knight::Knight(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : Piece(pieceColor, pieceType, value, cellIndex)
{
}

Knight::Knight(const Piece& other) : Piece(other)
{

}

std::vector<std::shared_ptr<Move>> Knight::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{};

	const Cell* cell = &(chessboard[this->cellIndex]);
	int row = this->cellIndex / Board::row_width;
	int column = this->cellIndex % Board::col_height;

	int index = this->cellIndex;
	int checkIndex = 0;


	if (row <= 5)
	{
		checkIndex = (row + 2) * 8 + column + 1;
		if (column <= 6 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}

		checkIndex = (row + 2) * 8 + column - 1;
		if (column >= 1 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}
	}

	if (row >= 2)
	{
		checkIndex = (row - 2) * 8 + column + 1;
		if (column <= 6 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}

		checkIndex = (row - 2) * 8 + column - 1;
		if (column >= 1 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}
	}

	if (column <= 5)
	{
		checkIndex = (row + 1) * 8 + column + 2;
		if (row <= 6 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}

		checkIndex = (row - 1) * 8 + column + 2;
		if (row >= 1 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}
	}

	if (column >= 2)
	{
		checkIndex = (row + 1) * 8 + column - 2;
		if (row <= 6 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}

		checkIndex = (row - 1) * 8 + column - 2;
		if (row >= 1 && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		{
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
		}
	}

	return answer;
}
