#include "King.h"
#include "../Board.h"
#include "../Cell/Cell.h"
#include "../Player/Player.h"
#include "../Moves/CastleMove.h"

King::King(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : Piece(pieceColor, pieceType, value, cellIndex)
{
}

King::King(const Piece& other) : Piece(other)
{

}


std::vector<std::shared_ptr<Move>> King::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{};

	const Player& cur_player = chessboard.GetPlayer(this->color);
	const Cell* cell = &(chessboard[this->cellIndex]);

	int row = this->cellIndex / Board::row_width;
	int column = this->cellIndex % Board::col_height;

	int index = this->cellIndex;
	int checkIndex = 0;

	bool isOnLeft = column == 0, isOnRight = column == 7, isOnTop = row == 7, isOnBottom = row == 0;

	if (!isOnTop)
	{
		//&& !chessboard.IsCellAttackedByEnemyPiece(checkIndex, this->color)
		// 
		// up 
		checkIndex = (row + 1) * 8 + column;
		if (!chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		// up left
		checkIndex = (row + 1) * 8 + column - 1;
		if (!isOnLeft && !chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		// up right
		checkIndex = (row + 1) * 8 + column + 1;
		if (!isOnRight && !chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
	}

	if (!isOnBottom)
	{
		// bottom 
		checkIndex = (row - 1) * 8 + column;
		if (!chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		// bottom left
		checkIndex = (row - 1) * 8 + column - 1;
		if (!isOnLeft && !chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

		// bottom right
		checkIndex = (row - 1) * 8 + column + 1;
		if (!isOnRight && !chessboard[checkIndex].IsThereFriendPiece(this->color))
			answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));
	}

	// right
	checkIndex = row * 8 + column + 1;
	if (!isOnRight && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));

	// left
	checkIndex = row * 8 + column - 1;
	if (!isOnLeft && !chessboard[checkIndex].IsThereFriendPiece(this->color))
		answer.push_back(std::make_shared<Move>(index, checkIndex, checkIndex, Move::MoveType::Move));


	// if king is attacked OR we check the available valid moves for opposite king (to check if our king is attacked by enemy king)
	// don't check for castle variants
	if (chessboard.GetCurrentPlayer()->GetColor() != this->color && chessboard.IsCellAttackedByEnemyPiece(index, this->color)) return answer;

	if (cur_player.GetCanCastleLong())
	{
		bool canCastleLongLocal = true;
		// check for 2 left cells
		for (int i = 1; i < 3; i++)
		{
			if (chessboard[index - i].IsTherePiece())
			{
				canCastleLongLocal = false;
				break;
			}
			if (chessboard.IsCellAttackedByEnemyPiece(index - i, this->color))
			{
				canCastleLongLocal = false;
				break;
			}
		}
		if (canCastleLongLocal)
		{
			answer.push_back(std::make_shared<CastleMove>(index, index - 2));
		}
	}

	if (cur_player.GetCanCastleShort())
	{
		bool canCastleShort = true;
		// check for 2 left cells
		for (int i = 1; i < 3; i++)
		{
			if (chessboard[index + i].IsTherePiece())
			{
				canCastleShort = false;
				break;
			}
			if (chessboard.IsCellAttackedByEnemyPiece(index + i, this->color))
			{
				canCastleShort = false;
				break;
			}
		}

		if (canCastleShort)
		{
			answer.push_back(std::make_shared<CastleMove>(index, index + 2));
		}
	}


	return answer;
}
