#include "Pawn.h"
#include "../Board.h"
#include "../Cell/Cell.h"
#include "../Moves/Move.h"
#include "../Moves/PromotionMove.h"


std::shared_ptr<Move> Pawn::CreatePawnMove(Piece::PieceColor currentColor, int fromCell, int toCell,
	int capturedPieceCell, Move::MoveType moveType) const
{
	int toRow = toCell / Board::row_width;

	if ((currentColor == Piece::PieceColor::Black && toRow == 0) || 
		(currentColor == Piece::PieceColor::White && toRow == 7) ) 
		return std::make_shared<PromotionMove>(fromCell, toCell, capturedPieceCell);

	return std::make_shared<Move>(fromCell, toCell, capturedPieceCell, Move::MoveType::Move);
}


Pawn::Pawn(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : 
	Piece(pieceColor, pieceType, value, cellIndex)
{
}

Pawn::Pawn(const Piece& other): Piece(other)
{

}

std::vector<std::shared_ptr<Move>> Pawn::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{};

	const Cell* cell = &(chessboard[this->cellIndex]);
	int row = this->cellIndex / Board::row_width;
	int column = this->cellIndex % Board::col_height;
	
	int index = this->cellIndex;
	int checkIndex = 0;

	if (this->color == Piece::PieceColor::White)
	{	
		checkIndex = index + 8;
		if (!chessboard[checkIndex].IsTherePiece())
			answer.push_back(CreatePawnMove(this->color, index, checkIndex, -1, Move::MoveType::Move));

		checkIndex = index + 16;
		if (cell->GetCellName()[1] == '2' && !chessboard[index + 8].IsTherePiece() && !chessboard[checkIndex].IsTherePiece())
			answer.push_back(CreatePawnMove(this->color, index, checkIndex, -1, Move::MoveType::Move));

		checkIndex = (row + 1) * 8 + column - 1;
		if (column != 0 && chessboard[checkIndex].IsThereEnemyPiece(this->color))
			answer.push_back(CreatePawnMove(this->color, index, checkIndex, 
				checkIndex, Move::MoveType::Move));

		checkIndex = (row + 1) * 8 + column + 1;
		if (column != 7 && chessboard[checkIndex].IsThereEnemyPiece(this->color))
			answer.push_back(CreatePawnMove(this->color, index, checkIndex,
				checkIndex, Move::MoveType::Move));

		// mistake with enPassant captured piece
		if (this->enPassantCell != nullptr)
			answer.push_back(std::make_shared<EnPassantMove>(index, enPassantCell->GetCellIndex(),
				enPassantCell->GetCellIndex() - 8, Move::MoveType::EnPassant));
	}
	else
	{
		checkIndex = index - 8;
		if (!chessboard[checkIndex].IsTherePiece())
			answer.push_back(CreatePawnMove(this->color, index, checkIndex, -1, Move::MoveType::Move));

		checkIndex = index - 16;
		if (cell->GetCellName()[1] == '7' && !chessboard[index - 8].IsTherePiece() && !chessboard[index - 16].IsTherePiece())
			answer.push_back(CreatePawnMove(this->color, index, checkIndex, -1, Move::MoveType::Move));

		checkIndex = (row - 1) * 8 + column - 1;
		if (column != 0 && chessboard[checkIndex].IsThereEnemyPiece(this->color))
			answer.push_back(CreatePawnMove(this->color, index, checkIndex,
				checkIndex, Move::MoveType::Move));

		checkIndex = (row - 1) * 8 + column + 1;
		if (column != 7 && chessboard[checkIndex].IsThereEnemyPiece(this->color))
			answer.push_back(CreatePawnMove(this->color, index, checkIndex,
				checkIndex, Move::MoveType::Move));

		if (this->enPassantCell != nullptr)
			answer.push_back(std::make_shared<EnPassantMove>(index, enPassantCell->GetCellIndex(),
				enPassantCell->GetCellIndex() + 8, Move::MoveType::EnPassant));
	}


	return answer;
}

Cell* Pawn::GetEnPassantCell() const
{
	return this->enPassantCell;
}

void Pawn::SetEnPassantCell(Cell* newEnPassantCell)
{
	this->enPassantCell = newEnPassantCell;
}
