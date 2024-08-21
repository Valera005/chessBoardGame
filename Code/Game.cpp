#include "Game.h"

void Game::SetBoard()
{
	// clear Players Info
	playerWhite.pieces.clear();
	playerWhite.caprutedPieces.clear();

	playerBlack.pieces.clear();
	playerBlack.caprutedPieces.clear();

	// set up White pieces
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "a1" });
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "h1" });

	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "b1" });
	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "g1" });

	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "c1" });
	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "f1" });

	playerWhite.pieces.push_back(Bishop{ Configuration::whiteQueenRect, Piece::PieceColor::White, "d1" });
	playerWhite.pieces.push_back(Bishop{ Configuration::whiteKingRect, Piece::PieceColor::White, "e1" });

	for (int i = 0; i < 8; i++)
	{
		playerWhite.pieces.push_back(Pawn{ Configuration::whitePawnRect, Piece::PieceColor::White, chessBoard.IndexToCellName(8 + i) });
	}

	// set up Black pieces
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "a8" });
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "h8" });

	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "b8" });
	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "g8" });

	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "c8" });
	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "f8" });

	playerBlack.pieces.push_back(Bishop{ Configuration::blackQueenRect, Piece::PieceColor::Black, "d8" });
	playerBlack.pieces.push_back(Bishop{ Configuration::blackKingRect, Piece::PieceColor::Black, "e8" });

	for (int i = 0; i < 8; i++)
	{
		playerBlack.pieces.push_back(Pawn{ Configuration::blackPawnRect, Piece::PieceColor::Black, chessBoard.IndexToCellName(48 + i) });
	}

	for (int i = 0; i < playerWhite.pieces.size(); i++)
	{
		chessBoard[playerWhite.pieces[i].cellName].SetPiece(&playerWhite.pieces[i]);
	}

	for (int i = 0; i < playerBlack.pieces.size(); i++)
	{
		chessBoard[playerBlack.pieces[i].cellName].SetPiece(&playerBlack.pieces[i]);
	}
}

Game::Game()
{
	Configuration::InitialiseTextures();

	gameStates = Configuration::GameStates::Running;
	
	SetBoard();
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



