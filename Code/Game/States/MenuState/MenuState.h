#pragma once
#include "../State.h"

class GameState;

class MenuState: public State
{
public:
	MenuState(StateManager& stateManager, sf::RenderWindow& window);
};

