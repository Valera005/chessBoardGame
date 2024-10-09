#pragma once
#include "../Pieces/Piece.h"
#include <string>
class Cell
{
	Piece* piece = nullptr;
	int cellIndex;
	std::string cellName;
public:

	Cell(int cellIndex, Piece* piece = nullptr);
	Cell(const Cell& other);
	void SetPiece(Piece* piece);
	Piece* GetPiece() const;
	const std::string& GetCellName() const;
	int GetCellIndex() const;
	bool IsTherePiece() const;
	bool IsThereFriendPiece(Piece::PieceColor color) const;
	bool IsThereEnemyPiece(Piece::PieceColor color) const;
};

