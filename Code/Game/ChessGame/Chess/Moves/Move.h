#pragma once
#include "../Pieces/Piece.h"

class Board;
class Cell;
class MoveValidator;

class Move
{
public:
	enum class MoveType {
		Move,
		Promotion,
		Castle,
		EnPassant,
	};

	virtual void execute(Board& board);

	Move(int fromCell, int toCell, int capturedPieceCell, MoveType type);
	Move(const Move& other);
	Move(Move&& other) noexcept;

	int GetToCell() const;

	friend class Board;
	friend class Cell;
	friend class Piece;
	friend class MoveValidator;

	bool operator==(const Move& other) const;
protected:
	int fromCell, toCell, capturedPieceCell;
	MoveType type;
	bool isCapturedPiece = false;
	Piece::PieceType movedPieceType;
};

