#pragma once
#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "..\ChessPieces\Piece.h"

class ChessBoardCell : public sf::Drawable
{
	static sf::Vector2f cellDimensions;
	sf::RectangleShape sprite{ cellDimensions };
	sf::Color cellColor;
	Piece* piecePtr = nullptr;

public:

	bool isSelected = false;
	bool isPointedTo = false;

	class CellColors 
	{
	public:
		static sf::Color Green;
		static sf::Color White;
	};

	ChessBoardCell(sf::Vector2f position, sf::Color cellColor);

	Piece* GetPiece() const;
	void SetPiece(Piece* piece);

	bool operator==(const ChessBoardCell& other);

	static const sf::Vector2f& getCellDimensions();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void PointTo();
	void UnPointTo();
};

