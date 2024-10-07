#pragma once
#include "Move.h"

class CastleMove : public Move
{
	int rookFromCell = 0;
	int rookToCell = 0;
public:
	
	CastleMove(int fromCell, int toCell);
	CastleMove(const CastleMove& other);
	CastleMove(CastleMove&& other) noexcept;

	virtual void execute(Board& board) const override;
};

