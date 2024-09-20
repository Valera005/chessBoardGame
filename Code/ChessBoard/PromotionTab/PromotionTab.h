#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "../ChessPieces/Piece.h"
#include "../ChessBoardCell/ChessBoardCell.h"
#include "../../Configuration/Configuration.h"
#include "vector"
#include "array"

class PromotionTab : public sf::Drawable
{

public:

	PromotionTab(sf::Vector2u windowSize);

	sf::Vector2f initialCoords{ 1000,100 };
	bool isToShow = false;
	Piece::PieceColor currentColor;

	std::vector<sf::RectangleShape> whiteBackgroundShapes;
	std::array<Piece::PieceType, 4> pieceTypes{Piece::PieceType::Queen, Piece::PieceType::Rook, 
		Piece::PieceType::Bishop, Piece::PieceType::Knight};

	sf::Sprite queenSprite;
	sf::Sprite rookSprite;
	sf::Sprite bishopSprite;
	sf::Sprite knightSprite;

	void Initialise(sf::Texture& chessPiecesTexture);

	void setSpritesForColor(Piece::PieceColor newColor);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	Piece::PieceType ProcessMousePressed(sf::Vector2i mousePosition, bool &isMouseHit);
};

