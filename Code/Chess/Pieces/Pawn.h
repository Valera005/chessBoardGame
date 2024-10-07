#pragma once
#include "Piece.h"
#include "../Moves/Move.h"

class Pawn : public Piece
{
	Cell* enPassantCell = nullptr;
public:

	friend class Board;

	Pawn(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex = -1);
	Pawn(const Piece& other);

	virtual std::vector<std::shared_ptr<Move>> GetValidMoves(const Board& chessboard) const override;
	virtual ~Pawn() {}

	Cell* GetEnPassantCell() const;
	void SetEnPassantCell(Cell* newEnPassantCell);

	std::shared_ptr<Move> CreatePawnMove(Piece::PieceColor currentColor, int fromCell, int toCell,
		int capturedPieceCell, Move::MoveType moveType) const;

};

