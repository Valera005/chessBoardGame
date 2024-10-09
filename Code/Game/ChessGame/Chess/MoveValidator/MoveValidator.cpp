#include "MoveValidator.h"
#include "../Board.h"
#include "../Pieces/Piece.h"


Board::MoveExecutionStatus MoveValidator::isValidMove(Move& move, const Board& board)
{

	Piece* currentPiece = board[move.fromCell].GetPiece();
	if (currentPiece == nullptr) return Board::MoveExecutionStatus::NotValid;

	if (board.currentPlayer->GetColor() != currentPiece->color) return Board::MoveExecutionStatus::NotValid;

	// check if this move is generally valid
	auto validMoves = board[move.fromCell].GetPiece()->GetValidMoves(board);

	bool isInValidMoves = false;

	for (int i = 0; i < validMoves.size(); i++)
	{
		if (move == *validMoves[i]) isInValidMoves = true;
	}

	if (!isInValidMoves) return Board::MoveExecutionStatus::NotValid;

	// if it is generally valid, check if king is not checked after it
	Board tempBoard(board);
	move.execute(tempBoard);

	if (IsKingInCheck(currentPiece->color, tempBoard)) return Board::MoveExecutionStatus::KingChecked;

	return Board::MoveExecutionStatus::Executed;
}

std::vector<std::shared_ptr<Move>> MoveValidator::filterValidMoves(const std::vector<std::shared_ptr<Move>>& moves, const Board& board)
{
	std::vector<std::shared_ptr<Move>> filteredMoves;

	Board tempBoard(board);

	for (int i = 0; i < moves.size(); i++)
	{
		tempBoard.CopyBoard(board);
		moves[i]->execute(tempBoard);

		if (!IsKingInCheck(tempBoard[moves[i]->toCell].GetPiece()->color, tempBoard))
		{
			filteredMoves.push_back(moves[i]);
		};
	}

	return filteredMoves;
}

bool MoveValidator::IsKingInCheck(Piece::PieceColor kingColor, const Board& board)
{
	Piece* king = board.GetKing(kingColor);

	return board.IsCellAttackedByEnemyPiece(king->cellIndex, kingColor);
}
