#pragma once
#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "..\ChessPieces\Piece.h"
#include "../GreyCircles/GreyCircle.h"

class CellReadAnimation;

class ChessBoardCell : public sf::Drawable
{
	static sf::Vector2f cellDimensions;
	sf::RectangleShape sprite{ cellDimensions };
	sf::Color cellColor;
	Piece* piecePtr = nullptr;
	Piece* previousPiecePtr = nullptr;
	
public:

	bool isShowGreyCircle = false;
	GreyCircle greyCircle;
	
	friend class CellReadAnimation;

	bool isSelected = false;
	bool isPointedTo = false;
	int cellIndex;
	std::string cellName;

	class CellColors 
	{
	public:
		static sf::Color Green;
		static sf::Color White;
	};

	ChessBoardCell(sf::Vector2f position, sf::Color cellColor, int cellIndex, std::string cellName);

	Piece* GetPiece() const;
	void SetPiece(Piece* piece);
	void Revert();

	bool operator==(const ChessBoardCell& other);

	static const sf::Vector2f& getCellDimensions();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void PointTo();
	void UnPointTo();

	bool isTherePiece();
	bool isThereFriendPiece(Piece::PieceColor color);
	bool isThereEnemyPiece(Piece::PieceColor color);

	bool isThereEnemyPiece(Piece::PieceColor color, Piece::PieceType pieceType);

	void ShowGreyCircle();
	void UnshowGreyCircle();
};

