#include "Game.h"



Game::Game()
{
	
	
}

void Game::HandleInput()
{

	sf::Event myEvent;

	while (window.pollEvent(myEvent));
	{
		switch (myEvent.type)
		{

		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyReleased:
			HandleKeyPress(myEvent.key.code);
			break;

		case sf::Event::MouseMoved:
			HandleMouseMoved(myEvent.mouseMove);
			break;
		
		case sf::Event::MouseButtonPressed:
			if (myEvent.mouseButton.button == sf::Mouse::Left)
				chessBoard.ProcessMousePressed(sf::Vector2i{ myEvent.mouseButton.x, myEvent.mouseButton.y });
			break;

		case sf::Event::MouseButtonReleased:
			if (myEvent.mouseButton.button == sf::Mouse::Left)
				chessBoard.ProcessMouseReleased(sf::Vector2i{ myEvent.mouseButton.x, myEvent.mouseButton.y });
			break;

		default:
			break;
		}

	}
}

void Game::HandleKeyPress(sf::Keyboard::Key& key)
{

	switch (key)
	{

	case sf::Keyboard::Escape:
		window.close();
		break;

	default:
		break;
	}

}

void Game::HandleMouseMoved(sf::Event::MouseMoveEvent& mousePosition)
{
	int x = mousePosition.x;
	int y = mousePosition.y;

	chessBoard.ProcessMouseMoved(mousePosition);

}

void Game::Update()
{
	sf::Time deltaTime = gameClock.restart();

}

void Game::Render()
{
	window.clear();

	window.draw(chessBoard);

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



