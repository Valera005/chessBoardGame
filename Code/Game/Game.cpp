#include "Game.h"

Game::Game(): stateManager(window)
{
	Utils::InitialiseUtils();
	stateManager.SetState(std::make_unique<MenuState>(stateManager, window));
}

void Game::HandleInput()
{

	sf::Event eventGame;

	while (window.pollEvent(eventGame));
	{
		switch (eventGame.type)
		{

		case sf::Event::Closed:
			window.close();
			break;

		default:
			this->stateManager.HandleEvent(eventGame);
			break;
		}
	}
}

void Game::HandleKeyPress(sf::Keyboard::Key& key)
{
}


void Game::Update()
{
	sf::Time deltaTime = gameClock.restart();
	this->stateManager.Update(deltaTime);
}

void Game::Render()
{
	window.clear();

	this->stateManager.Draw(window);

	window.display();
}



void Game::Run()
{
	while (window.isOpen())
	{
		HandleInput();

		Update();

		Render();
	}
}
