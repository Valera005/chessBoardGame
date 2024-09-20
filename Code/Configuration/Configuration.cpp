#include "Configuration.h"

sf::Texture Configuration::chessPiecesTexture{};

sf::IntRect Configuration::whiteKingRect
{ Configuration::pieceWidth * 5, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::whiteQueenRect
{ Configuration::pieceWidth * 4, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::whiteBishopRect
{ Configuration::pieceWidth * 2, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::whiteKnightRect
{ Configuration::pieceWidth * 1, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::whiteRookRect
{ Configuration::pieceWidth * 3, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::whitePawnRect
{ Configuration::pieceWidth * 0, Configuration::pieceHeight * 1, Configuration::pieceWidth, Configuration::pieceHeight };


sf::IntRect Configuration::blackKingRect
{ Configuration::pieceWidth * 5, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::blackQueenRect
{ Configuration::pieceWidth * 4, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::blackBishopRect
{ Configuration::pieceWidth * 2, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::blackKnightRect
{ Configuration::pieceWidth * 1, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::blackRookRect
{ Configuration::pieceWidth * 3, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };

sf::IntRect Configuration::blackPawnRect
{ Configuration::pieceWidth * 0, Configuration::pieceHeight * 0, Configuration::pieceWidth, Configuration::pieceHeight };


void Configuration::InitialiseTextures()
{
	if (!Configuration::chessPiecesTexture.loadFromFile("Resources/Images/ChessPiecesSpriteSheet.png"))
	{
		throw("Can't load ChessSpriteSheet");
	}
}
