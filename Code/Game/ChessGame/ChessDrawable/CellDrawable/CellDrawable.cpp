#include "CellDrawable.h"
#include "../PieceDrawable/PieceDrawable.h"

sf::Color CellDrawable::CellColors::Green{ 115, 149, 82 };
sf::Color CellDrawable::CellColors::White{ 235, 236, 208 };
sf::Vector2f const CellDrawable::cellDimensions{ 110,110 };

CellDrawable::CellDrawable(Cell& cell, const sf::Vector2f& position, const sf::Color& color):
	cell(cell), color(color), greyCircle(position)
{
	this->sprite.setOrigin(cellDimensions.x / 2, cellDimensions.y / 2);

	this->sprite.setFillColor(color);
	this->sprite.setPosition(position);
}

void CellDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
	//if (pieceDrawable != nullptr && !pieceDrawable->piecePtr.expired()) target.draw(*pieceDrawable);
	//if (this->toShowGreyCircle) target.draw(greyCircle);
}

void CellDrawable::PointTo()
{
	if (this->color == CellColors::White)
		this->sprite.setFillColor({ 240, 241, 212 });
	else
		this->sprite.setFillColor({ 120, 160, 90 });
}

void CellDrawable::UnPointTo()
{
	this->sprite.setFillColor(this->color);
}

void CellDrawable::SetShowGreyCircle(bool toShowGreyCircle)
{
	this->toShowGreyCircle = toShowGreyCircle;
}

bool CellDrawable::GetShowGreyCircle() const
{
	return toShowGreyCircle;
}

void CellDrawable::SetPieceDrawable(PieceDrawable* newPieceDrawable)
{
	this->pieceDrawable = newPieceDrawable;
	if(pieceDrawable) 
		this->pieceDrawable->setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y));
}

PieceDrawable* CellDrawable::GetPieceDrawable() const
{
	return pieceDrawable;
}
