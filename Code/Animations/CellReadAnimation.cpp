#include "CellReadAnimation.h"

CellReadAnimation::CellReadAnimation(ChessBoardCell* chessCell) : chessCell(chessCell)
{

}

void CellReadAnimation::Update(sf::Time deltaTime)
{
	timeSinceLastFrame += deltaTime;

	if (isAnimationRunning && timeSinceLastFrame >= timeOfChange)
	{
		currentFrame++;
		timeSinceLastFrame = sf::Time::Zero;
		if (currentFrame == 1)
		{
			this->chessCell->sprite.setFillColor(sf::Color::Red);
		}
		else if (currentFrame == 2)
		{
			this->chessCell->sprite.setFillColor(chessCell->cellColor);
			currentFrame = 0;
			isAnimationRunning = false;
		}
	}
}

void CellReadAnimation::Start()
{
	isAnimationRunning = true;
	currentFrame = 0;
	timeSinceLastFrame = this->timeOfChange;
}

void CellReadAnimation::SetCell(ChessBoardCell* newCell)
{
	this->chessCell = newCell;
}
