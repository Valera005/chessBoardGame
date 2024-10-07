#include "ChessGame.h"

ChessGame::ChessGame() : board(), boardDrawable(board, window.getSize())
{
	
}

void ChessGame::HandleInput()
{
	
	sf::Event myEvent;

	while (window.pollEvent(myEvent));
	{
		switch (myEvent.type)
		{

		case sf::Event::Closed:
			window.close();
			break;

		//case sf::Event::KeyReleased:
		//	HandleKeyPress(myEvent.key.code);
		//	break;

		//case sf::Event::MouseButtonPressed:
		//	if (myEvent.mouseButton.button == sf::Mouse::Left)
		//		chessBoard.ProcessMousePressed(sf::Vector2i{ myEvent.mouseButton.x, myEvent.mouseButton.y });
		//	break;

		//case sf::Event::MouseButtonReleased:
		//	if (myEvent.mouseButton.button == sf::Mouse::Left)
		//		chessBoard.ProcessMouseReleased(sf::Vector2i{ myEvent.mouseButton.x, myEvent.mouseButton.y });
		//	break;

		default:
			boardDrawable.HandleEvent(myEvent);
			break;
		}

	}
}

void ChessGame::HandleKeyPress(sf::Keyboard::Key& key)
{
}


void ChessGame::Update()
{

	sf::Time deltaTime = gameClock.restart();

}

void ChessGame::Render()
{
	window.clear();

	boardDrawable.Draw(window);

	window.display();
}



void ChessGame::Run()
{
	while (window.isOpen())
	{
		HandleInput();

		Update();

		Render();
	}
}
