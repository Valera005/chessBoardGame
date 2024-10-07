#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "./Chess/Board.h"
#include "./ChessDrawable/BoardDrawable.h"

class ChessGame
{
	sf::VideoMode windowSize{ 1920, 1080 };
	sf::RenderWindow window{ windowSize, "Chess Game" };

	sf::Clock gameClock;

	Board board;
	BoardDrawable boardDrawable;


	void HandleInput();

	void HandleKeyPress(sf::Keyboard::Key& key);

	void Update();
	void Render();

public:

	ChessGame();

	void Run();
};

