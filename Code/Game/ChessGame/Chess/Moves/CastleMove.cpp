#include "CastleMove.h"
#include "../Board.h"

CastleMove::CastleMove(int fromCell, int toCell): 
	Move(fromCell, toCell, -1, Move::MoveType::Castle)
{	

}

CastleMove::CastleMove(const CastleMove& other):
	Move(other.fromCell, other.toCell, other.capturedPieceCell, other.type)
{

}

CastleMove::CastleMove(CastleMove&& other) noexcept: 
	Move(other.fromCell, other.toCell, other.capturedPieceCell, other.type) 
{
	this->rookFromCell = other.rookFromCell;
	this->toCell = other.rookToCell;
}

void CastleMove::execute(Board& board)
{
	Piece* king = board[this->fromCell].GetPiece();

	// if toCell->fromcell > 0 - this is Short Castle
	if (this->toCell - this->fromCell > 0)
	{
		Piece* rook = board[this->fromCell + 3].GetPiece();

		board[this->toCell].SetPiece(board[this->fromCell].GetPiece());
		board[this->fromCell].SetPiece(nullptr);

		board[rook->GetCellIndex()].SetPiece(nullptr);
		board[rook->GetCellIndex() - 2].SetPiece(rook);
	}
	else
	{
		Piece* rook = board[this->fromCell - 4].GetPiece();

		board[this->toCell].SetPiece(board[this->fromCell].GetPiece());
		board[this->fromCell].SetPiece(nullptr);

		board[rook->GetCellIndex()].SetPiece(nullptr);
		board[rook->GetCellIndex() + 3].SetPiece(rook);
	}

	Player& player = board.GetPlayer(king->GetPieceColor());
	player.SetCanCastleLong(false);
	player.SetCanCastleShort(false);
}
