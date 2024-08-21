#include "ChessBoard.h"
#include <iostream>
using std::cout, std::endl;

ChessBoard::ChessBoard(sf::Vector2u windowSize)
{
	cells.reserve(size);

	int width = windowSize.x;
	int height = windowSize.y; 

	sf::Vector2i center(width / 2, height / 2);
	
	sf::Vector2f cellDimensions = ChessBoardCell::getCellDimensions();

	sf::Vector2i leftBottom(center.x - cellDimensions.x * 3.5, center.y + cellDimensions.y * 3.5);

	chessBoardRect = sf::IntRect( center.x - cellDimensions.x * 4,
		center.y - cellDimensions.y * 4, cellDimensions.x * 8, cellDimensions.y * 8 );

	for (int i = 0; i < size; i++)
	{
		if (((i % 2) + (int)((i / 8) % 2)) % 2 == 0)
			cells.emplace_back(sf::Vector2f{ (float)leftBottom.x + ((i % 8) * cellDimensions.x), (float)leftBottom.y - ((i / 8) * cellDimensions.y) }, ChessBoardCell::CellColors::Green);
		else
			cells.emplace_back(sf::Vector2f{ (float)leftBottom.x + ((i % 8) * cellDimensions.x), (float)leftBottom.y - ((i / 8) * cellDimensions.y) }, ChessBoardCell::CellColors::White);
	}

}

void ChessBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < size; i++)
	{
		target.draw(cells[i]);
	}

	for (int i = 0; i < size; i++)
	{
		Piece* piece = cells[i].GetPiece();
		if(piece!=nullptr)
			target.draw(*piece);
	}
}

int ChessBoard::CellNameToIndex(const std::string& cellName)
{
	if (cellName.length() != 2) throw std::exception("Cell Name size has to be 2 letters length");

	if (cellName[0] >= 'a' && cellName[0] <= 'h' && cellName[1] >= '1' && cellName[1] <= '8')
	{
		return ((cellName[1] - '0' - 1) * 8) + (cellName[0] - 'a'); // row * 8 + column
	}
	else throw std::exception("Bad cell name");
	
}

std::string ChessBoard::IndexToCellName(int index)
{
	if (index < 0 || index > 63) throw std::exception("Index has to be btw 0-64");

	std::string cellName = "00";
	
	cellName[0] = (char)(index % 8 + 'a');
	cellName[1] = (char)(index / 8 + '1');

	return cellName;
}

ChessBoardCell& ChessBoard::operator[](const std::string& cellName)
{
	return cells[CellNameToIndex(cellName)];
}

void ChessBoard::ProcessMouseMoved(sf::Event::MouseMoveEvent& mousePosition)
{
	int index = GetIndexByCoords({mousePosition.x, mousePosition.y});
	
	if (index >= 0 && index <= 63)
	{
		if (this->pointedCell != &cells[index])
		{
			if(this->pointedCell != nullptr) this->pointedCell->UnPointTo();
			this->pointedCell = &cells[index];
			pointedCell->PointTo();
		}
	}
	else
	{
		if (this->pointedCell != nullptr)
		{
			this->pointedCell->UnPointTo();
		}
		this->pointedCell = nullptr;
	}

	if (selectedCell)
	{
		selectedCell->GetPiece()->setSpritePosition(mousePosition.x, mousePosition.y);
	}
}

void ChessBoard::ProcessMousePressed(sf::Vector2i mousePosition)
{
	if (pointedCell != nullptr && selectedCell == nullptr)
	{
		selectedCell = pointedCell;
	}
	else if (selectedCell)
	{
		selectedCell->GetPiece()->setSpritePosition(mousePosition.x, mousePosition.y);
	}

}

void ChessBoard::ProcessMouseReleased(sf::Vector2i mousePosition)
{
	if (selectedCell != nullptr)
	{
		if (pointedCell != nullptr && pointedCell != selectedCell)
		{
			pointedCell->SetPiece(selectedCell->GetPiece());
		}
		else 
		{
			selectedCell->SetPiece(selectedCell->GetPiece());
		}

		selectedCell = nullptr;
	}
}

int ChessBoard::GetIndexByCoords(const sf::Vector2i coords)
{
	int x = coords.x;
	int y = coords.y;

	if (!chessBoardRect.contains({ x,y })) return -1;

	sf::Vector2i leftBottom{ chessBoardRect.left, chessBoardRect.top + chessBoardRect.height };

	sf::Vector2i coordsDelta{ x - leftBottom.x, std::abs(y - leftBottom.y) };

	int row = coordsDelta.y / ChessBoardCell::getCellDimensions().y;
	int column = coordsDelta.x / ChessBoardCell::getCellDimensions().x;
	int index = row * 8 + column;

	return index;
}


