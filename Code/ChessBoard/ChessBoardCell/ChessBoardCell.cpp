#include "ChessBoardCell.h"

sf::Color ChessBoardCell::CellColors::Green{ 115, 149, 82 };
sf::Color ChessBoardCell::CellColors::White{ 235, 236, 208 };
sf::Vector2f ChessBoardCell::cellDimensions{ 110,110 };

ChessBoardCell::ChessBoardCell(sf::Vector2f position, sf::Color cellColor, int cellIndex, std::string cellName) 
	: cellIndex(cellIndex), 
	cellName(cellName),
	greyCircle(position)
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
	this->previousPiecePtr = this->piecePtr;
	this->piecePtr = piece;
	if (piece == nullptr) return;

	this->piecePtr->cellName = this->cellName;
	this->piecePtr->setSpritePosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void ChessBoardCell::Revert()
{
	this->piecePtr = previousPiecePtr;
	this->SetPiece(previousPiecePtr);
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

bool ChessBoardCell::isTherePiece()
{
	return this->GetPiece() != nullptr;
}

bool ChessBoardCell::isThereFriendPiece(Piece::PieceColor color)
{
	return isTherePiece() && this->GetPiece()->color == color;
}

bool ChessBoardCell::isThereEnemyPiece(Piece::PieceColor color)
{
	return isTherePiece() && this->GetPiece()->color != color;
}

bool ChessBoardCell::isThereEnemyPiece(Piece::PieceColor color, Piece::PieceType pieceType)
{
	return isTherePiece() && this->GetPiece()->color != color && this->piecePtr->type == pieceType;
}

void ChessBoardCell::ShowGreyCircle()
{
	isShowGreyCircle = true;
}

void ChessBoardCell::UnshowGreyCircle()
{
	isShowGreyCircle = false;
}


