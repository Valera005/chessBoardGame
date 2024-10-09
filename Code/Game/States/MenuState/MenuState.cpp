#include "MenuState.h"
#include "../../StateManager/StateManager.h"
#include "../GameState/GameState.h"
#include "../Button/Button.h"

void f() {}

MenuState::MenuState(StateManager& stateManager, sf::RenderWindow& window) : State(stateManager, window)
{
	sf::Vector2f center(window.getSize().x / 2, window.getSize().y / 2);

	sf::Vector2f pos1(center.x, center.y - 100);

	buttons.emplace_back(pos1, "Play", Utils::RobotoFont, 80,
		[this]() {
			this->SetState(std::make_unique<GameState>(this->GetStateManager(), this->GetWindow()));
		});

	sf::Vector2f pos2(center.x, center.y + 100);
	buttons.emplace_back(pos2, "Exit", Utils::RobotoFont, 80,
		[this]() {
			this->CloseWindow();
		});

}



