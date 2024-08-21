#include "Timer.h"

void sf::Timer::Update()
{
	if (isRunning)
		this->elapsedTime += clock.restart();
	else
		clock.restart();
}

sf::Timer::Timer(sf::Time duration)
{
	this->duration = duration;
	this->elapsedTime = sf::Time::Zero;
}

bool sf::Timer::SetDuration(sf::Time& newDuration)
{
	if (!isRunning)
	{
		this->duration = newDuration;
		return 1;
	}

	return 0;
}


sf::Time sf::Timer::GetRemainingTime()
{
	Update();
	sf::Time remainingTime = this->duration - this->elapsedTime;
	return (remainingTime > sf::Time::Zero) ? remainingTime : sf::Time::Zero;
}

sf::Time sf::Timer::GetElapsedTime()
{
	Update();
	return elapsedTime;
}

void sf::Timer::Start()
{
	clock.restart();
	isRunning = true;
}

void sf::Timer::Stop()
{
	if (isRunning)
	{
		Update();
		isRunning = false;
	}
}

void sf::Timer::Reset()
{
	this->elapsedTime = sf::Time::Zero;
	isRunning = true;
	clock.restart();
}

bool sf::Timer::IsExpired()
{
	return GetRemainingTime() > sf::Time::Zero;
}


