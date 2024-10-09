#include "GameState.h"
#include "../../StateManager/StateManager.h"
#include "../MenuState/MenuState.h"

GameState::GameState(StateManager& stateManager, sf::RenderWindow& window) : State(stateManager, window), chessGame(window)
{
	sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
	
	sf::Vector2i rightMiddle(center.x + CellDrawable::cellDimensions.x * 4, center.y);


	sf::Vector2f pos1(rightMiddle.x + 200, rightMiddle.y - 100);
	buttons.emplace_back(pos1, "Reset\nBoard", Utils::RobotoFont, 60,
		[this]() {
			this->chessGame.ResetGame();
		});


	sf::Vector2f pos2(rightMiddle.x + 181, rightMiddle.y + 100);
	buttons.emplace_back(pos2, "Back", Utils::RobotoFont, 60,
		[this]() {
			this->SetState(std::make_unique<MenuState>(this->GetStateManager(), this->GetWindow()));
		});


	gameStateText.setFont(Utils::RobotoFont);
	gameStateText.setString(this->GetStringGameState(chessGame.GetGameState()));
	gameStateText.setCharacterSize(35);
	gameStateText.setPosition(rightMiddle.x + 63, rightMiddle.y - 300);
	gameStateText.setFillColor(sf::Color::White);
}

void GameState::HandleEvent(const sf::Event& eventGame)
{
	if (chessGame.GetGameState() == Board::GameState::Running)
		chessGame.HandleEvent(eventGame);

	State::HandleEvent(eventGame);
}

void GameState::Update(const sf::Time& deltaTime)
{
	chessGame.Update(deltaTime);

	gameStateText.setString(this->GetStringGameState(chessGame.GetGameState()));
}

void GameState::Draw(sf::RenderTarget& target)
{
	chessGame.Draw(target);
	target.draw(gameStateText);

	State::Draw(target);
}

std::string GameState::GetStringGameState(Board::GameState gameState)
{
	switch (gameState)
	{
	case Board::GameState::Running:
		return "Running";
		break;

	case Board::GameState::Checkmate:
		return (chessGame.GetWinnerPlayer()->GetColor() == Piece::PieceColor::White) ? "Checkmate, White won" : "Checkmate, Black won";
		break;

	case Board::GameState::Stalemate:
		return "Stalemate";
		break;

	case Board::GameState::DrawInsufficientMaterial:
		return "Draw due to material";
		break;

	case Board::GameState::DrawFiveTimesRepetition:
		return "Draw due to 5 repetition";
		break;

	case Board::GameState::DrawFiftyMoves:
		return "Draw due to 50 moves rule";
		break;

	default:
		return "Invalid State";
		break;
	}

}


