#include "Piece.h"

Piece::Piece(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex)
{
	this->color = pieceColor;
	this->type = pieceType;
	this->value = value;
	this->cellIndex = cellIndex;
}

Piece::Piece(const Piece& other)
{
	this->color = other.color;
	this->type = other.type;
	this->value = other.value;
	this->cellIndex = other.cellIndex;
	this->isCaptured = other.isCaptured;
}

int Piece::GetCellIndex() const
{
	return cellIndex;
}

Piece::PieceColor Piece::GetPieceColor() const
{
	return this->color;
}

int Piece::GetValue() const
{
	return value;
}

bool Piece::GetIsCaptured() const
{
	return isCaptured;
}

void Piece::SetIsCaptured(bool isCaptured)
{
	this->isCaptured = isCaptured;
}

Piece::PieceType Piece::GetPieceType() const
{
	return this->type;
}
