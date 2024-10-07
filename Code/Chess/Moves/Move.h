#pragma once

class Board;
class Cell;
class Piece;
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

	virtual void execute(Board& board) const;

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
};

