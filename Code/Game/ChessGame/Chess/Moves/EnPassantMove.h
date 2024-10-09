#pragma once
#include "./Move.h"


class EnPassantMove : public Move
{

public:

	EnPassantMove(int fromCell, int toCell, int capturedPieceCell, MoveType type);

	bool operator==(const EnPassantMove& other);
	virtual void execute(Board& board) override;
};

