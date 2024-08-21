#pragma once
#include "ChessPieces/AllPieces.h"
#include "ChessBoardCell/ChessBoardCell.h"
#include "SFML/Window/Event.hpp"
#include <array>

class ChessBoard : public sf::Drawable
{
	std::vector<ChessBoardCell> cells;
	const int static size = 64;

	ChessBoardCell* pointedCell;
	ChessBoardCell* selectedCell;

public:

	ChessBoard(sf::Vector2u windowSize);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	static int CellNameToIndex(const std::string& cellName);
	static std::string IndexToCellName(int index);

	ChessBoardCell& operator[](const std::string& cellName);

	void ProcessMouseMoved(sf::Event::MouseMoveEvent& mousePosition);

	void ProcessMousePressed(sf::Vector2i mousePosition);

	void ProcessMouseReleased(sf::Vector2i mousePosition);

	int GetIndexByCoords(const sf::Vector2i coords);

	sf::IntRect chessBoardRect;
};

