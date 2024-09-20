#include "PromotionTab.h"

PromotionTab::PromotionTab(sf::Vector2u windowSize)
{
	int width = windowSize.x;
	int height = windowSize.y;

	sf::Vector2i center(width / 2, height / 2);

	sf::Vector2f cellDimensions = ChessBoardCell::getCellDimensions();

	initialCoords.x = center.x + cellDimensions.x * 6;
	initialCoords.y = center.y - cellDimensions.y * 3.5;


	for (int i = 0; i < 4; i++)
	{
		sf::RectangleShape whiteBackgroundShape;

		whiteBackgroundShape.setSize(sf::Vector2f(cellDimensions.x, cellDimensions.y));
		whiteBackgroundShape.setOrigin(cellDimensions.x / 2, cellDimensions.y / 2);
		whiteBackgroundShape.setPosition(initialCoords.x, initialCoords.y + cellDimensions.y * i);
		whiteBackgroundShape.setOutlineColor(sf::Color(128, 128, 128));
		whiteBackgroundShape.setOutlineThickness(2);

		whiteBackgroundShapes.push_back(whiteBackgroundShape);
	}
	
}


void PromotionTab::Initialise(sf::Texture& chessPiecesTexture)
{
	queenSprite.setTexture(chessPiecesTexture);
	rookSprite.setTexture(chessPiecesTexture);
	bishopSprite.setTexture(chessPiecesTexture);
	knightSprite.setTexture(chessPiecesTexture);

	queenSprite.setTextureRect(Configuration::whiteQueenRect);
	rookSprite.setTextureRect(Configuration::whiteRookRect);
	bishopSprite.setTextureRect(Configuration::whiteBishopRect);
	knightSprite.setTextureRect(Configuration::whiteKnightRect);

	queenSprite.setOrigin(queenSprite.getLocalBounds().width / 2, queenSprite.getLocalBounds().height / 2);
	rookSprite.setOrigin(rookSprite.getLocalBounds().width / 2, rookSprite.getLocalBounds().height / 2);
	bishopSprite.setOrigin(bishopSprite.getLocalBounds().width / 2, bishopSprite.getLocalBounds().height / 2);
	knightSprite.setOrigin(knightSprite.getLocalBounds().width / 2, knightSprite.getLocalBounds().height / 2);

	sf::Vector2f cellDimensions = ChessBoardCell::getCellDimensions();

	queenSprite.setPosition(sf::Vector2f(initialCoords.x, initialCoords.y + cellDimensions.x * 0));
	rookSprite.setPosition(sf::Vector2f(initialCoords.x, initialCoords.y + cellDimensions.x * 1));
	bishopSprite.setPosition(sf::Vector2f(initialCoords.x, initialCoords.y + cellDimensions.x * 2));
	knightSprite.setPosition(sf::Vector2f(initialCoords.x, initialCoords.y + cellDimensions.x * 3));
}

void PromotionTab::setSpritesForColor(Piece::PieceColor newColor)
{	
	currentColor = newColor;
	if (newColor == Piece::PieceColor::White)
	{
		queenSprite.setTextureRect(Configuration::whiteQueenRect);
		rookSprite.setTextureRect(Configuration::whiteRookRect);
		bishopSprite.setTextureRect(Configuration::whiteBishopRect);
		knightSprite.setTextureRect(Configuration::whiteKnightRect);
	}
	else
	{
		queenSprite.setTextureRect(Configuration::blackQueenRect);
		rookSprite.setTextureRect(Configuration::blackRookRect);
		bishopSprite.setTextureRect(Configuration::blackBishopRect);
		knightSprite.setTextureRect(Configuration::blackKnightRect);
	}
}

void PromotionTab::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < whiteBackgroundShapes.size(); i++)
	{
		target.draw(whiteBackgroundShapes[i]);
	}
	target.draw(queenSprite);
	target.draw(rookSprite);
	target.draw(bishopSprite);
	target.draw(knightSprite);
}

Piece::PieceType PromotionTab::ProcessMousePressed(sf::Vector2i mousePosition, bool& isMouseHit)
{
	isMouseHit = false;
	int intersectionIndex = 0;

	for (int i = 0; i < whiteBackgroundShapes.size(); i++)
	{
		if (whiteBackgroundShapes[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			intersectionIndex = i;
			isMouseHit = true;
			isToShow = false;
			break;
		}
	}

	return pieceTypes[intersectionIndex];
}
