#pragma once
#include "../ChessBoard/ChessBoardCell/ChessBoardCell.h"
#include "SFML/System/Clock.hpp"
class CellReadAnimation
{
	ChessBoardCell* chessCell;
	sf::Time timeOfChange{ sf::seconds(0.5) };
	sf::Time timeSinceLastFrame{ sf::Time::Zero };
	int currentFrame = 0;
	bool isAnimationRunning = false;

public:
	
	CellReadAnimation(ChessBoardCell* chessCell = nullptr);

	void Update(sf::Time deltaTime);

	void Start();
	void SetCell(ChessBoardCell* newCell);
};

