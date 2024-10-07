#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Configuration
{
public:

	static const int pieceWidth = 128;
	static const int pieceHeight = 128;

	static sf::IntRect whiteKingRect;
	static sf::IntRect whiteQueenRect;
	static sf::IntRect whitePawnRect;
	static sf::IntRect whiteRookRect;
	static sf::IntRect whiteKnightRect;
	static sf::IntRect whiteBishopRect;

	static sf::IntRect blackKingRect;
	static sf::IntRect blackQueenRect;
	static sf::IntRect blackPawnRect;
	static sf::IntRect blackRookRect;
	static sf::IntRect blackKnightRect;
	static sf::IntRect blackBishopRect;

	static sf::Texture chessPiecesTexture;

	static void InitialiseTextures();
};

