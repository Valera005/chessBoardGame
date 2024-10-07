#include "PromotionMove.h"

PromotionMove::PromotionMove(int fromCell, int toCell, int capturedPieceCell):
	Move(fromCell, toCell, capturedPieceCell, Move::MoveType::Promotion)
{

}

void PromotionMove::execute(Board& board) const
{
	if (capturedPieceCell != -1 && board[capturedPieceCell].GetPiece() != nullptr) board[capturedPieceCell].GetPiece()->SetIsCaptured(true);

	// autoQueen is enabled ahahah
	Piece* pawn = board[this->fromCell].GetPiece();
	board[this->fromCell].SetPiece(nullptr);

	// create queen
	board.pieces.emplace_back(std::make_shared<Queen>(
		pawn->GetPieceColor(), Piece::PieceType::Queen, 9, this->toCell));
	
	// make the cell point to the queen
	board[this->toCell].SetPiece(board.pieces[board.pieces.size() - 1].get());

	// delete the pawn from pieces
	for (int i = 0, size = board.pieces.size(); i < size; i++)
	{
		if (board.pieces[i].get() == pawn)
		{
			board.pieces.erase(board.pieces.begin() + i);
			break;
		}
	}

}
