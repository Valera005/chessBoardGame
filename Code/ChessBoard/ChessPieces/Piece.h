#pragma once
#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "..\..\Configuration\Configuration.h"


class Piece : public sf::Drawable
{
public:

	std::string cellName;

	enum class PieceColor
	{
		White,
		Black
	};

	Piece(const sf::Texture& pieceTexture, const sf::IntRect& pieceRect, const PieceColor& color, const std::string& cellName);

	virtual ~Piece() {}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSpritePosition(float x, float y);

	virtual int GetValue() const;

private:

	sf::Sprite pieceSprite;
	PieceColor color;

};

