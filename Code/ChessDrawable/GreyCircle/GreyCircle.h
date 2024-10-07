#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class GreyCircle : public sf::Drawable
{
	sf::CircleShape circle{ 25, 50 };
public:
	GreyCircle();
	GreyCircle(sf::Vector2f position);

	const sf::CircleShape& getCircle() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

