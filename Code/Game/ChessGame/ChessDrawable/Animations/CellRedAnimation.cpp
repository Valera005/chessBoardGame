#include "CellRedAnimation.h"

CellRedAnimation::CellRedAnimation(CellDrawable* chessCell) : chessCell(chessCell)
{

}

void CellRedAnimation::Update(sf::Time deltaTime)
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
			this->chessCell->sprite.setFillColor(chessCell->color);
			currentFrame = 0;
			isAnimationRunning = false;
		}
	}
}

void CellRedAnimation::Start()
{
	isAnimationRunning = true;
	currentFrame = 0;
	timeSinceLastFrame = this->timeOfChange;
}

void CellRedAnimation::SetCell(CellDrawable* newCell)
{
	this->chessCell = newCell;
}
