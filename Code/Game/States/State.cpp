#include "State.h"
#include "../StateManager/StateManager.h"

State::State(StateManager& stateManager, sf::RenderWindow& window): stateManager(stateManager), window(window)
{

}

void State::SetState(std::unique_ptr<State> newState)
{
	stateManager.SetState(std::move(newState));
}

void State::CloseWindow()
{
	this->window.close();
}

sf::RenderWindow& State::GetWindow()
{
	return window;
}

StateManager& State::GetStateManager()
{
	return stateManager;
}


void State::HandleEvent(const sf::Event& eventGame)
{

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].HandleEvent(eventGame);
	}

}

void State::Update(const sf::Time& deltaTime)
{

}

void State::Draw(sf::RenderTarget& target)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].Draw(target);
	}
}