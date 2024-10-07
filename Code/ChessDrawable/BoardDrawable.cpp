#include "BoardDrawable.h"
#include <iostream>

BoardDrawable::BoardDrawable(Board& board, sf::Vector2u windowSize): board(board)
{
	Configuration::InitialiseTextures();
	int width = windowSize.x;
	int height = windowSize.y;

	sf::Vector2i center(width / 2, height / 2);

	sf::Vector2f cellDimensions = CellDrawable::cellDimensions;

	sf::Vector2i leftBottom(center.x - cellDimensions.x * 3.5, center.y + cellDimensions.y * 3.5);

	chessBoardRect = sf::IntRect(center.x - cellDimensions.x * 4,
		center.y - cellDimensions.y * 4, cellDimensions.x * 8, cellDimensions.y * 8);

	cellsDrawable.reserve(64);

	for (int i = 0; i < board.size; i++)
	{
		if (((i % 2) + (int)((i / board.row_width) % 2)) % 2 == 0)
			cellsDrawable.emplace_back(board[i], sf::Vector2f{ (float)leftBottom.x + ((i % board.row_width) * cellDimensions.x), (float)leftBottom.y - ((i / board.row_width) * cellDimensions.y) }, CellDrawable::CellColors::Green);
		else
			cellsDrawable.emplace_back(board[i], sf::Vector2f{ (float)leftBottom.x + ((i % board.row_width) * cellDimensions.x), (float)leftBottom.y - ((i / board.row_width) * cellDimensions.y) }, CellDrawable::CellColors::White);
	}

	this->UpdateBoardState();
}

void BoardDrawable::Draw(sf::RenderTarget& target) const
{
	for (int i = 0; i < cellsDrawable.size(); i++)
	{
		target.draw(cellsDrawable[i]);
	}

	for (int i = 0; i < piecesDrawable.size(); i++)
	{
		if(!(piecesDrawable[i].piecePtr.lock()->GetIsCaptured())) target.draw(piecesDrawable[i]);
	}

	for (int i = 0; i < cellsDrawable.size(); i++)
	{
		if (cellsDrawable[i].toShowGreyCircle) target.draw(cellsDrawable[i].greyCircle);
	}

	if (selectedCell && selectedCell->GetPieceDrawable()) target.draw(*selectedCell->GetPieceDrawable());
}


void BoardDrawable::SelectCell(CellDrawable* cell)
{
	if (cell->cell.GetPiece() == nullptr) return;
	selectedCell = cell;
	this->ShowGreyCircles(cell->GetPieceDrawable());

}

void BoardDrawable::DeselectCell()
{
	if (selectedCell == nullptr) return;
	this->HideGreyCircles();
	selectedCell = nullptr;
}


void BoardDrawable::HandleEvent(const sf::Event& eventChess)
{

	int cellIndex = -1;

	switch (eventChess.type)
	{

	case sf::Event::MouseButtonPressed:

		if (pointedCell != nullptr && selectedCell == nullptr && pointedCell->GetPieceDrawable() != nullptr
			&& board.GetCurrentPlayer()->GetColor() == pointedCell->GetPieceDrawable()->piecePtr.lock()->GetPieceColor())
		{
			this->SelectCell(pointedCell);
		}
		else if (selectedCell)
		{
			selectedCell->GetPieceDrawable()->setPosition(sf::Vector2f(eventChess.mouseButton.x, eventChess.mouseButton.y));
		}
		break;

	case sf::Event::MouseMoved:

		cellIndex = GetCellIndex({ eventChess.mouseMove.x, eventChess.mouseMove.y });
		
		if (cellIndex != -1)
		{
			if (this->pointedCell == nullptr || this->pointedCell->cell.GetCellIndex() != cellIndex)
			{
				if (this->pointedCell != nullptr) this->pointedCell->UnPointTo();
				this->pointedCell = &cellsDrawable[cellIndex];
				pointedCell->PointTo();
			}
		}
		else
		{
			if (this->pointedCell != nullptr) this->pointedCell->UnPointTo();
			this->pointedCell = nullptr;
		}

		if (selectedCell)
		{
			selectedCell->GetPieceDrawable()->setPosition(sf::Vector2f(eventChess.mouseMove.x, eventChess.mouseMove.y));
		}

		break;


	case sf::Event::MouseButtonReleased:

		if (selectedCell != nullptr)
		{

			if (pointedCell != nullptr && pointedCell != selectedCell &&
				pointedCell->toShowGreyCircle == true)
			{	
				if (board.Execute(selectedCell->cell.GetCellIndex(), pointedCell->cell.GetCellIndex()))
				{
					this->UpdateBoardState();
				}
			}
			else
			{
				cellAnimation.SetCell(&cellsDrawable[board.GetKing(board.GetCurrentPlayer()->GetColor())->GetCellIndex()]);
				cellAnimation.Start();
				selectedCell->SetPieceDrawable(selectedCell->GetPieceDrawable());
			}

			this->DeselectCell();
		}

		break;

	default:
		break;
	}

}

void BoardDrawable::Update(const sf::Time& deltaTime)
{
	if (cellAnimation.isAnimationRunning) cellAnimation.Update(deltaTime);
}

int BoardDrawable::GetCellIndex(sf::Vector2i mousePosition)
{
	if (!chessBoardRect.contains(mousePosition)) return -1;

	sf::Vector2i leftBottom{ chessBoardRect.left, chessBoardRect.top + chessBoardRect.height };

	int x_coord = mousePosition.x - leftBottom.x;
	int y_coord = std::abs(mousePosition.y - leftBottom.y);

	int row = y_coord / CellDrawable::cellDimensions.y;
	int col = x_coord / CellDrawable::cellDimensions.x;

	if (row * 8 + col < 0 || row * 8 + col > 63) return -1;
	
	return (row * 8 + col);
}


void BoardDrawable::ShowGreyCircles(PieceDrawable* piece)
{
	if (piece == nullptr) return;

	this;

	auto allValidMoves = board[piece->piecePtr.lock()->GetCellIndex()]
		.GetPiece()->GetValidMoves(board);
	
	auto validMoves = MoveValidator::filterValidMoves(allValidMoves, board);

	for (int i = 0; i < validMoves.size(); i++)
	{
		cellsDrawable[validMoves[i]->GetToCell()].SetShowGreyCircle(true);
	}
}

void BoardDrawable::HideGreyCircles()
{
	for (int i = 0; i < cellsDrawable.size(); i++) cellsDrawable[i].SetShowGreyCircle(false);
}

void BoardDrawable::NullAllCells()
{
	for (int i = 0; i < cellsDrawable.size(); i++)
	{
		cellsDrawable[i].SetPieceDrawable(nullptr);
	}
}

void BoardDrawable::UpdateBoardState()
{
	this->NullAllCells();
	this->piecesDrawable.clear();

	auto pieces = board.GetPieces();
	piecesDrawable.reserve(pieces.size() + 5);
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->GetIsCaptured()) continue;
		//Create new PieceDrawable
		this->piecesDrawable.push_back(PieceDrawable::CreatePieceDrawable(pieces[i]));

		//Get the right cell for it
		CellDrawable& pieceCell = cellsDrawable[pieces[i]->GetCellIndex()];

		pieceCell.SetPieceDrawable(&piecesDrawable[piecesDrawable.size()-1]);
		continue;
	}
}
