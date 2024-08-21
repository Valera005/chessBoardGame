#include "ChessBoard.h"
#include <iostream>
using std::cout, std::endl;

void ChessBoard::SetBoard()
{
	// clear Players Info
	playerWhite.pieces.clear();
	playerWhite.caprutedPieces.clear();

	playerBlack.pieces.clear();
	playerBlack.caprutedPieces.clear();

	// set up White pieces
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "a1" });
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "h1" });

	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "b1" });
	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "g1" });

	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "c1" });
	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "f1" });

	playerWhite.pieces.push_back(Bishop{ Configuration::whiteQueenRect, Piece::PieceColor::White, "d1" });
	playerWhite.pieces.push_back(Bishop{ Configuration::whiteKingRect, Piece::PieceColor::White, "e1" });

	for (int i = 0; i < 8; i++)
	{
		playerWhite.pieces.push_back(Pawn{ Configuration::whitePawnRect, Piece::PieceColor::White, this->IndexToCellName(8 + i) });
	}

	// set up Black pieces
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "a8" });
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "h8" });

	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "b8" });
	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "g8" });

	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "c8" });
	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "f8" });

	playerBlack.pieces.push_back(Bishop{ Configuration::blackQueenRect, Piece::PieceColor::Black, "d8" });
	playerBlack.pieces.push_back(Bishop{ Configuration::blackKingRect, Piece::PieceColor::Black, "e8" });

	for (int i = 0; i < 8; i++)
	{
		playerBlack.pieces.push_back(Pawn{ Configuration::blackPawnRect, Piece::PieceColor::Black, this->IndexToCellName(48 + i) });
	}

	for (int i = 0; i < playerWhite.pieces.size(); i++)
	{
		(*this)[playerWhite.pieces[i].cellName].SetPiece(&playerWhite.pieces[i]);
	}

	for (int i = 0; i < playerBlack.pieces.size(); i++)
	{
		(*this)[playerBlack.pieces[i].cellName].SetPiece(&playerBlack.pieces[i]);
	}

	
}

ChessBoard::ChessBoard(sf::Vector2u windowSize)
{
	Configuration::InitialiseTextures();

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

	SetBoard();
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

	if (selectedCell != nullptr && selectedCell->GetPiece() != nullptr)
		target.draw(*(selectedCell->GetPiece()));
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

ChessBoardCell& ChessBoard::operator[](const int& index)
{
	return cells[index];
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
	if (pointedCell != nullptr && selectedCell == nullptr && pointedCell->GetPiece() != nullptr)
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
		if (pointedCell != nullptr && pointedCell != selectedCell && isAllowedToMoveToCell(selectedCell, pointedCell))
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

bool ChessBoard::isAllowedToMoveToCell(ChessBoardCell* cellFrom, ChessBoardCell* cellTo)
{
	Piece* temp = cellFrom->GetPiece();
	std::vector<ChessBoardCell*> allowedCells = temp->getAllowedCellsToMove(*this);

	for (int i = 0; i < allowedCells.size(); i++)
	{
		if (cellTo == allowedCells[i]) return true;
	}

	return false;
}


