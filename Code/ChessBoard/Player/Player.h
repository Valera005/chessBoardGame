#pragma once
#include "..\ChessPieces\Piece.h"
#include "..\..\Tools\Timer.h"
#include <vector>

class Player
{
public:

	enum class CastleVariants {
		Short,
		Long
	};

	bool canCastleShort = true;
	bool canCastleLong = true;

	std::string name = "Valee";
	sf::Timer timer;

	std::vector<Piece> pieces;
	std::vector<Piece> caprutedPieces;

	Piece::PieceColor piecesColor;

	Player(Piece::PieceColor color);
};

