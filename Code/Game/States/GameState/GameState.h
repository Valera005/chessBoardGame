#pragma once
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

	ChessGame chessGame;
};

