#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "Utils/Utils.h"
#include "./StateManager/StateManager.h"
#include "./States/MenuState/MenuState.h"


class Game
{
	sf::VideoMode windowSize{ 1920, 1080 };
	sf::RenderWindow window{ windowSize, "Chess Game" };

	StateManager stateManager;
	sf::Clock gameClock;

	void HandleInput();
	void HandleKeyPress(sf::Keyboard::Key& key);
	void Update();
	void Render();

public:

	Game();

	void Run();
};

