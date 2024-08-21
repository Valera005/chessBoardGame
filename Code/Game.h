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
	Player playerWhite{ Piece::PieceColor::White };
	Player playerBlack{ Piece::PieceColor::Black };

	int turn = 0;
	bool isWhiteMoves = true;
	bool isCheck = false;
	bool isCheckMate = false;

	Configuration::GameStates gameStates = Configuration::GameStates::Menu;

	void HandleInput();
	
	void HandleKeyPress(sf::Keyboard::Key& key);
	void HandleMouseMoved(sf::Event::MouseMoveEvent& mousePosition);

	void Update();
	void Render();

	void SetBoard();

public:

	Game();

	void Run();


};

