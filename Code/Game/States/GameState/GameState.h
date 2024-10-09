#pragma once
#include <string>
#include "../State.h"
#include "../../ChessGame/ChessGame.h"

class MenuState;

class GameState: public State
{
public:
	GameState(StateManager& stateManager, sf::RenderWindow& window);

	virtual void HandleEvent(const sf::Event& eventGame) override;
	virtual void Update(const sf::Time& deltaTime) override;
	virtual void Draw(sf::RenderTarget& target) override;

	std::string GetStringGameState(Board::GameState gameState);

	ChessGame chessGame;
	sf::Text gameStateText;
};

