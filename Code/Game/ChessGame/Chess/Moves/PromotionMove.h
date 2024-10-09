#pragma once
#include "Move.h"
#include "../Board.h"

class PromotionMove : public Move
{
public:

	PromotionMove(int fromCell, int toCell, int capturedPieceCell);

	virtual void execute(Board& board) override;
};

