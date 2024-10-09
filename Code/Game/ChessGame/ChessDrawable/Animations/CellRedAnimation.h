#pragma once
#include "../CellDrawable/CellDrawable.h"
#include "SFML/System/Clock.hpp"

class CellRedAnimation
{
	CellDrawable* chessCell;
	sf::Time timeOfChange{ sf::seconds(0.5) };
	sf::Time timeSinceLastFrame{ sf::Time::Zero };
	int currentFrame = 0;
	bool isAnimationRunning = false;

	friend class BoardDrawable;

public:
	
	CellRedAnimation(CellDrawable* chessCell = nullptr);

	void Update(sf::Time deltaTime);

	void Start();
	void SetCell(CellDrawable* newCell);
};

