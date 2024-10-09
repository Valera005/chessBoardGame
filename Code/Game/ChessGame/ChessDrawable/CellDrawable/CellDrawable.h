#pragma once
#include <SFML/Graphics.hpp>
#include "../../Chess/Cell/Cell.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../GreyCircle/GreyCircle.h"

class PieceDrawable;

class CellDrawable: public sf::Drawable
{
public:
	static const sf::Vector2f cellDimensions;

	class CellColors
	{
	public:
		static sf::Color Green;
		static sf::Color White;
	};

    CellDrawable(Cell& cell, const sf::Vector2f& position, const sf::Color& color);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void PointTo();
	void UnPointTo();

	void SetShowGreyCircle(bool toShowGreyCircle);
	bool GetShowGreyCircle() const;

	friend class BoardDrawable;
	friend class CellRedAnimation;

	void SetPieceDrawable(PieceDrawable* newPieceDrawable);
	PieceDrawable* GetPieceDrawable() const;

private:
	const sf::Color color;
    Cell& cell;
	PieceDrawable* pieceDrawable = nullptr;
	sf::RectangleShape sprite{ cellDimensions };
	GreyCircle greyCircle;
	bool toShowGreyCircle = false;
};

