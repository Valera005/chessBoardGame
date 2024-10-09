#include "PieceDrawable.h"
#include "../../Configuration/Configuration.h"

PieceDrawable::PieceDrawable(std::shared_ptr<Piece>& piece, sf::Texture& texture, sf::IntRect& textureRect): piecePtr(piece)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(textureRect);
	
	sprite.setOrigin(textureRect.width / 2, textureRect.height / 2);
	sprite.setScale(1, 1);
}

PieceDrawable::PieceDrawable(const PieceDrawable& other)
{
	this->sprite = other.sprite;
	this->piecePtr = other.piecePtr;
}

PieceDrawable::PieceDrawable(PieceDrawable&& other) noexcept
{
	this->sprite = std::move(other.sprite);
	this->piecePtr = std::move(other.piecePtr);
	
}

void PieceDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}

void PieceDrawable::setPosition(const sf::Vector2f& position)
{
	this->sprite.setPosition(position);
}

PieceDrawable PieceDrawable::CreatePieceDrawable(std::shared_ptr<Piece>& piece)
{

	switch (piece->GetPieceType())
	{

	case Piece::PieceType::Pawn:
		if(piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whitePawnRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackPawnRect);
		break;

	case Piece::PieceType::Bishop:
		if (piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whiteBishopRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackBishopRect);
		break;

	case Piece::PieceType::King:
		if (piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whiteKingRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackKingRect);
		break;

		case Piece::PieceType::Knight:
		if (piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whiteKnightRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackKnightRect);
		break;

	case Piece::PieceType::Queen:
		if (piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whiteQueenRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackQueenRect);
		break;

	case Piece::PieceType::Rook:
		if (piece->GetPieceColor() == Piece::PieceColor::White)
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::whiteRookRect);
		else
			return PieceDrawable(piece, Configuration::chessPiecesTexture, Configuration::blackRookRect);
		break;

	default:
		throw std::exception("No such piece type");
		break;
	}

	throw std::exception("No such piece type");
}
