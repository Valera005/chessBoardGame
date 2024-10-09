#include "Cell.h"
#include "../BoardUtils/BoardUtils.h"

Cell::Cell(int cellIndex, Piece* piece) : cellIndex(cellIndex), cellName(BoardUtils::IndexToCellName(cellIndex)), piece(piece)
{
}

Cell::Cell(const Cell& other) : cellIndex(other.cellIndex), cellName(BoardUtils::IndexToCellName(other.cellIndex)), piece(nullptr)
{

}

void Cell::SetPiece(Piece* piece)
{
	this->piece = piece;
	
	if (this->piece != nullptr)
		this->piece->cellIndex = this->cellIndex;
}

Piece* Cell::GetPiece() const
{
	return piece;
}

const std::string& Cell::GetCellName() const
{
	return cellName;
}

int Cell::GetCellIndex() const
{
	return cellIndex;
}

bool Cell::IsTherePiece() const
{
	return piece != nullptr;
}


bool Cell::IsThereFriendPiece(Piece::PieceColor color) const
{
	return IsTherePiece() && this->GetPiece()->color == color;
}

bool Cell::IsThereEnemyPiece(Piece::PieceColor color) const
{
	return IsTherePiece() && this->GetPiece()->color != color;
}

