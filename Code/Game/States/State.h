#pragma once
#include <vector>
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Font.hpp"
#include "./Button/Button.h"
#include "../Utils/Utils.h"

class StateManager;

class State
{

public:
	State(StateManager& stateManager, sf::RenderWindow& window);

	virtual void HandleEvent(const sf::Event& eventGame);
	virtual void Update(const sf::Time& deltaTime);
	virtual void Draw(sf::RenderTarget& target);
	virtual void SetState(std::unique_ptr<State> newState);

	virtual ~State() = default;

	void CloseWindow();

	sf::RenderWindow& GetWindow();
	StateManager& GetStateManager();

protected:
	std::vector<Button> buttons;
	sf::RenderWindow& window;
	StateManager& stateManager;
};

