#include "Piece.h"

Piece::Piece(const sf::Texture& pieceTexture, const sf::IntRect& pieceRect,const PieceColor& color, const std::string& cellName)
{
	pieceSprite.setTexture(pieceTexture);
	pieceSprite.setTextureRect(pieceRect);

	pieceSprite.setOrigin(pieceRect.width / 2, pieceRect.height / 2);
	pieceSprite.setScale(1, 1);

	this->color = color;
	this->cellName = cellName;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pieceSprite);
}

void Piece::setSpritePosition(float x, float y)
{
	pieceSprite.setPosition(x, y);
}

int Piece::GetValue() const
{
	return 0;
}

