#pragma once
#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "..\..\Configuration\Configuration.h"
#include <functional>

class ChessBoard;
class ChessBoardCell;

class Piece : public sf::Drawable
{
public:

	enum class PieceColor
	{
		White,
		Black
	};

	enum class PieceType
	{
		Pawn,
		Knight,
		Bishop,
		Rook,
		Queen,
		King
	};

	using GetAllowedCellsFuncType = std::function<std::vector<ChessBoardCell*>(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor color)>;

	GetAllowedCellsFuncType GetAllowedCellsFunc;

	Piece(const sf::Texture& pieceTexture, const sf::IntRect& pieceRect, const PieceColor& color, const std::string& cellName,
		const GetAllowedCellsFuncType& GetAllowedCells, PieceType pieceType);

	virtual ~Piece() {}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSpritePosition(float x, float y);

	virtual int GetValue() const;

	void BindAllowedCells(GetAllowedCellsFuncType& GetAllowedCellsFunc);
	
	PieceColor color;
	PieceType type;
	std::string cellName;

	bool isCaptured = false;

	bool isAllowedPassageCapture = false;
	ChessBoardCell* passageCaptureCell = nullptr;

protected:

	sf::Sprite pieceSprite;
};

