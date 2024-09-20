#include "GreyCircle.h"


GreyCircle::GreyCircle() 
{
	circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
	circle.setPosition(0, 0);
	circle.setFillColor(sf::Color(128, 128, 128, 160 ));
}


GreyCircle::GreyCircle(sf::Vector2f position)
{
	circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
	circle.setPosition(position);
	circle.setFillColor(sf::Color(128, 128, 128, 160));
}


const sf::CircleShape& GreyCircle::getCircle() const
{
	return circle;
}

void GreyCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle);
}
