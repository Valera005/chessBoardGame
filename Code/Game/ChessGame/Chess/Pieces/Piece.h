#pragma once
#include <vector>
#include <memory>

class Board;
class Cell;
class Move;
//class MoveValidator;

class Piece
{
public:

	enum class PieceColor
	{
		White,
		Black
	};

	enum class PieceType
	{
		Pawn,
		Knight,
		Bishop,
		Rook,
		Queen,
		King
	};

	friend class Cell;
	friend class Board;
	friend class MoveValidator;

	Piece(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Piece(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const = 0;

	int GetValue() const;
	int GetCellIndex() const;
	Piece::PieceColor GetPieceColor() const;

	virtual ~Piece() {}

	bool GetIsCaptured() const;
	void SetIsCaptured(bool isCaptured);
	
	PieceType GetPieceType() const;

protected:
	PieceColor color;
	PieceType type;
	int cellIndex;
	int value;
	bool isCaptured = false;
};

