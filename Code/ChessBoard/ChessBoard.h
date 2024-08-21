#pragma once
#include "ChessPieces/AllPieces.h"
#include "ChessBoardCell/ChessBoardCell.h"
#include "SFML/Window/Event.hpp"
#include "Player/Player.h"
#include <array>

class ChessBoard : public sf::Drawable
{
	std::vector<ChessBoardCell> cells;
	const int static size = 64;

	ChessBoardCell* pointedCell = nullptr;
	ChessBoardCell* selectedCell = nullptr;

	Player playerWhite{ Piece::PieceColor::White };
	Player playerBlack{ Piece::PieceColor::Black };

	int turn = 0;
	bool isWhiteMoves = true;
	bool isCheck = false;
	bool isCheckMate = false;

	Configuration::GameStates gameStates = Configuration::GameStates::Menu;

	void SetBoard();

public:

	ChessBoard(sf::Vector2u windowSize);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	static int CellNameToIndex(const std::string& cellName);
	static std::string IndexToCellName(int index);

	ChessBoardCell& operator[](const std::string& cellName);
	ChessBoardCell& operator[](const int& index);


	void ProcessMouseMoved(sf::Event::MouseMoveEvent& mousePosition);

	void ProcessMousePressed(sf::Vector2i mousePosition);

	void ProcessMouseReleased(sf::Vector2i mousePosition);

	int GetIndexByCoords(const sf::Vector2i coords);

	sf::IntRect chessBoardRect;

	bool isAllowedToMoveToCell(ChessBoardCell* cellFrom, ChessBoardCell* cellTo);
};

