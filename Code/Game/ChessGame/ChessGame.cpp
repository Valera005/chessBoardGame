#include "ChessGame.h"

ChessGame::ChessGame(sf::RenderWindow& window): board(), boardDrawable(board, window.getSize())
{
	
}

void ChessGame::HandleEvent(const sf::Event& eventGame)
{	
	boardDrawable.HandleEvent(eventGame);
}

void ChessGame::Update(const sf::Time& deltaTime)
{
	boardDrawable.Update(deltaTime);
}

void ChessGame::Draw(sf::RenderTarget& target)
{
	boardDrawable.Draw(target);
}

void ChessGame::ResetGame()
{
	boardDrawable.ResetBoard();
}


