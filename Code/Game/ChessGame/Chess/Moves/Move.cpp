#include "Move.h"
#include "../Board.h"

Move::Move(int fromCell, int toCell, int capturedPieceCell, MoveType type) :
	fromCell(fromCell), toCell(toCell), capturedPieceCell(capturedPieceCell), type(type)
{

}

Move::Move(const Move& other)
{
	this->fromCell = other.fromCell;
	this->toCell = other.toCell;
	this->capturedPieceCell = other.capturedPieceCell;
	this->type = other.type;
}

Move::Move(Move&& other) noexcept
{
	this->fromCell = other.fromCell;
	this->toCell = other.toCell;
	this->capturedPieceCell = other.capturedPieceCell;
	this->type = other.type;
}

int Move::GetToCell() const
{
	return toCell;
}

bool Move::operator==(const Move& other) const
{
	return this->fromCell == other.fromCell && this->toCell == other.toCell && this->type == other.type;
}

void Move::execute(Board& board)
{
	movedPieceType = board[this->fromCell].GetPiece()->GetPieceType();
	// classic Move execution
	if (capturedPieceCell != -1 && board[capturedPieceCell].GetPiece() != nullptr)
	{
		board[capturedPieceCell].GetPiece()->SetIsCaptured(true);
		isCapturedPiece = true;
	}

	board[this->toCell].SetPiece(board[this->fromCell].GetPiece());
	board[this->fromCell].SetPiece(nullptr);
}
