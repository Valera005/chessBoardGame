#include "Player.h"

Player::Player(Piece::PieceColor piecesColor)
{
	this->piecesColor = piecesColor;
}

Player::Player(const Player& other)
{
	this->canCastleLong = other.canCastleLong;
	this->canCastleShort = other.canCastleShort;
	this->name = other.name;
	this->piecesColor = other.piecesColor;
}

void Player::SetCanCastleShort(bool value)
{
	canCastleShort = value;
}

void Player::SetCanCastleLong(bool value)
{
	canCastleLong = value;
}

bool Player::GetCanCastleShort() const
{
	return canCastleShort;
}

bool Player::GetCanCastleLong() const
{
	return canCastleLong;
}

Piece::PieceColor Player::GetColor() const
{
	return this->piecesColor;
}
