#pragma once
#include "../Pieces/Piece.h"
#include <string>
#include <vector>

class Board;
class Cell;
class Piece;

class Player
{
	bool canCastleShort = true;
	bool canCastleLong = true;
	Piece::PieceColor piecesColor;
	std::string name = "Valee";

	//sf::Timer timer;
public:

	Player(Piece::PieceColor color);
	Player(const Player& other);

	friend class Board;
	friend class Cell;
	friend class Piece;

	enum class CastleVariants {
		Short,
		Long
	};

	void SetCanCastleShort(bool value);
	void SetCanCastleLong(bool value);

	bool GetCanCastleShort() const;
	bool GetCanCastleLong() const;

	Piece::PieceColor GetColor() const;
};

