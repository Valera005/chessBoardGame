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
	Board board;
	BoardDrawable boardDrawable;
public:

	ChessGame(sf::RenderWindow& window);

	void HandleEvent(const sf::Event& eventGame);
	void Update(const sf::Time& deltaTime);
	void Draw(sf::RenderTarget& target);

	void ResetGame();
	Board::GameState GetGameState() const;
	const Player* GetWinnerPlayer() const;
};

