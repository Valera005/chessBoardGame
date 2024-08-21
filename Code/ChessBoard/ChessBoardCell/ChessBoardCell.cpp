#include "ChessBoardCell.h"

sf::Color ChessBoardCell::CellColors::Green{ 115, 149, 82 };
sf::Color ChessBoardCell::CellColors::White{ 235, 236, 208 };
sf::Vector2f ChessBoardCell::cellDimensions{ 110,110 };

ChessBoardCell::ChessBoardCell(sf::Vector2f position, sf::Color cellColor)
{
	auto localBounds = this->sprite.getLocalBounds();
	this->sprite.setOrigin(localBounds.width / 2, localBounds.height / 2);

	this->cellColor = cellColor;
	this->sprite.setFillColor(cellColor);
	this->sprite.setPosition(position);
}

Piece* ChessBoardCell::GetPiece() const
{
	return piecePtr;
}

void ChessBoardCell::SetPiece(Piece* piece)
{
	this->piecePtr = piece;
	this->piecePtr->setSpritePosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

bool ChessBoardCell::operator==(const ChessBoardCell& other)

{
	return this->sprite.getGlobalBounds().left == other.sprite.getGlobalBounds().left &&
		this->sprite.getGlobalBounds().top == other.sprite.getGlobalBounds().top;
}

const sf::Vector2f& ChessBoardCell::getCellDimensions()
{
	return cellDimensions;
}




void ChessBoardCell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void ChessBoardCell::PointTo()
{
	isPointedTo = true;
	if(cellColor==CellColors::White)
		this->sprite.setFillColor({ 240, 241, 212 });
	else
		this->sprite.setFillColor({ 120, 160, 90 });

}

void ChessBoardCell::UnPointTo()
{
	isPointedTo = false;
	if (cellColor == CellColors::White)
		this->sprite.setFillColor(CellColors::White);
	else
		this->sprite.setFillColor(CellColors::Green);
}
