#include "GameState.h"
#include "../../StateManager/StateManager.h"
#include "../MenuState/MenuState.h"

GameState::GameState(StateManager& stateManager, sf::RenderWindow& window) : State(stateManager, window), chessGame(window)
{
	sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
	
	sf::Vector2i rightMiddle(center.x + CellDrawable::cellDimensions.x * 3.5, center.y);


	sf::Vector2f pos1(rightMiddle.x + 250, center.y - 100);
	buttons.emplace_back(pos1, "Reset\nBoard", Utils::RobotoFont, 60,
		[this]() {
			this->chessGame.ResetGame();
		});


	sf::Vector2f pos2(rightMiddle.x + 250, center.y + 100);
	buttons.emplace_back(pos2, "Back", Utils::RobotoFont, 60,
		[this]() {
			this->SetState(std::make_unique<MenuState>(this->GetStateManager(), this->GetWindow()));
		});

}

void GameState::HandleEvent(const sf::Event& eventGame)
{
	chessGame.HandleEvent(eventGame);

	State::HandleEvent(eventGame);
}

void GameState::Update(const sf::Time& deltaTime)
{
	chessGame.Update(deltaTime);

}

void GameState::Draw(sf::RenderTarget& target)
{
	chessGame.Draw(target);

	State::Draw(target);
}


