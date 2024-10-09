#include "StateManager.h"


StateManager::StateManager(sf::RenderWindow& window): window(window)
{
	currentState = nullptr;
}

void StateManager::HandleEvent(const sf::Event& eventGame)
{
	this->currentState->HandleEvent(eventGame);
}

void StateManager::Update(const sf::Time& deltaTime)
{
	this->currentState->Update(deltaTime);
}

void StateManager::Draw(sf::RenderTarget& target)
{
	this->currentState->Draw(target);
}

void StateManager::SetState(std::unique_ptr<State> newState)
{
	this->currentState = std::move(newState);
}

std::unique_ptr<State>& StateManager::GetState()
{
	return this->currentState;
}
