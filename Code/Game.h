#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Configuration/Configuration.h"
#include "ChessBoard/ChessBoard.h"
#include "ChessBoard/Player/Player.h"

class Game
{
	sf::VideoMode windowSize{ 1920, 1080 };
	sf::RenderWindow window{ windowSize, "Chess Game" };

	sf::Clock gameClock;

	ChessBoard chessBoard{ window.getSize() };



	void HandleInput();
	
	void HandleKeyPress(sf::Keyboard::Key& key);
	void HandleMouseMoved(sf::Event::MouseMoveEvent& mousePosition);

	void Update();
	void Render();

public:

	Game();

	void Run();

};

