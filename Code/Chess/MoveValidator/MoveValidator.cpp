#include "MoveValidator.h"
#include "../Board.h"

bool MoveValidator::isValidMove(const Move& move, const Board& board)
{

	Piece* currentPiece = board[move.fromCell].GetPiece();
	if (currentPiece == nullptr) return false;
	
	if (board.currentPlayer->GetColor() != currentPiece->color) return false;

	auto validMoves = MoveValidator::filterValidMoves(board[move.fromCell].GetPiece()->GetValidMoves(board), board);

	bool isInValidMoves = false;

	for (int i = 0; i < validMoves.size(); i++)
	{
		if (move == *validMoves[i]) isInValidMoves = true;
	}

	if (!isInValidMoves) return false;

	Board tempBoard(board);
	move.execute(tempBoard);
	
	if (IsKingInCheck(currentPiece->color, tempBoard)) return false;

	return true;
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
