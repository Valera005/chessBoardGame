#pragma once
#include <memory>
#include "../States/State.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Event.hpp"


class StateManager
{
public:
	StateManager(sf::RenderWindow& window);

	void HandleEvent(const sf::Event& eventGame);
	void Update(const sf::Time& deltaTime);
	void Draw(sf::RenderTarget& target);

	void SetState(std::unique_ptr<State> newState);
	std::unique_ptr<State>& GetState();

	sf::Window& window;

protected:
	std::unique_ptr<State> currentState;
};

