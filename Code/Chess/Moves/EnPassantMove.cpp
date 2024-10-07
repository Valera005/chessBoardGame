#include "EnPassantMove.h"
#include "../Board.h"

EnPassantMove::EnPassantMove(int fromCell, int toCell, int capturedPieceCell, MoveType type):
	Move(fromCell, toCell, capturedPieceCell, type)
{
}

bool EnPassantMove::operator==(const EnPassantMove& other)
{
	return this->fromCell == other.fromCell && this->toCell == other.toCell && 
		this->type == other.type && this->capturedPieceCell == other.capturedPieceCell;
}

void EnPassantMove::execute(Board& board) const
{
	if (capturedPieceCell != -1 && board[capturedPieceCell].GetPiece() != nullptr)
	{
		board[capturedPieceCell].GetPiece()->SetIsCaptured(true);
		board[capturedPieceCell].SetPiece(nullptr);
	}

	board[this->toCell].SetPiece(board[this->fromCell].GetPiece());
	board[this->fromCell].SetPiece(nullptr);
}
