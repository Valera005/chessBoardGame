#include "Board.h"
#include <iostream>
Board::Board() : playerWhite(Piece::PieceColor::White), playerBlack(Piece::PieceColor::Black), 
	currentPlayer(&playerWhite)
{
	cells.reserve(size);
	for (int i = 0; i < size; i++)
	{
		cells.push_back(Cell(i));
	}

	ResetBoard();
}

Board::Board(const Board& other) : playerWhite(other.playerWhite), playerBlack(other.playerBlack)
{
	cells.reserve(size);
	for (int i = 0; i < size; i++)
	{
		cells.push_back(Cell(i));
	}

	this->CopyBoard(other);
}

Cell& Board::operator[](int index)
{
	return cells[index];
}

Cell& Board::operator[](const std::string& cellName)
{
	return cells[BoardUtils::CellNameToIndex(cellName)];
}

const Cell& Board::operator[](int index) const
{
	return cells[index];
}

const Cell& Board::operator[](const std::string& cellName) const
{
	return cells[BoardUtils::CellNameToIndex(cellName)];
}


bool Board::Execute(int fromCell, int toCell)
{
	auto move = this->parseMove(fromCell, toCell);

	if (!MoveValidator::isValidMove(*move, *this)) return false;
	
	move->execute(*this);

	moves.emplace_back(move);

	UpdateCastleVariants(*move);

	UpdateEnPassant(*move);
	
	if (IsCheckMate())
	{
		winnerPlayer = currentPlayer;
		gameState = GameState::Checkmate;
	}
	else if (IsCheckMate())
	{
		gameState = GameState::Stalemate;
	}
	else if (IsDraw())
	{
		gameState = GameState::Draw;
	}

	ChangeCurrentPlayer();

	return true;
}


void Board::ResetBoard()
{
	this->NullAllCells();
	pieces.clear();

	//all white pieces
	pieces.push_back(std::make_shared<Rook>(Piece::PieceColor::White, Piece::PieceType::Rook, 5, BoardUtils::CellNameToIndex("a1")));
	pieces.push_back(std::make_shared<Rook>(Piece::PieceColor::White, Piece::PieceType::Rook, 5, BoardUtils::CellNameToIndex("h1")));

	pieces.push_back(std::make_shared<Knight>(Piece::PieceColor::White, Piece::PieceType::Knight, 3, BoardUtils::CellNameToIndex("b1")));
	pieces.push_back(std::make_shared<Knight>(Piece::PieceColor::White, Piece::PieceType::Knight, 3, BoardUtils::CellNameToIndex("g1")));

	pieces.push_back(std::make_shared<Bishop>(Piece::PieceColor::White, Piece::PieceType::Bishop, 3, BoardUtils::CellNameToIndex("c1")));
	pieces.push_back(std::make_shared<Bishop>(Piece::PieceColor::White, Piece::PieceType::Bishop, 3, BoardUtils::CellNameToIndex("f1")));

	pieces.push_back(std::make_shared<Queen>(Piece::PieceColor::White, Piece::PieceType::Queen, 9, BoardUtils::CellNameToIndex("d1")));
	pieces.push_back(std::make_shared<King>(Piece::PieceColor::White, Piece::PieceType::King, 100, BoardUtils::CellNameToIndex("e1")));

	for (int i = 0; i < row_width; i++)
	{
		pieces.push_back(std::make_shared<Pawn>(Piece::PieceColor::White, Piece::PieceType::Pawn, 1, i + 8));
	}

	//all black pieces
	pieces.push_back(std::make_shared<Rook>(Piece::PieceColor::Black, Piece::PieceType::Rook, 5, BoardUtils::CellNameToIndex("a8")));
	pieces.push_back(std::make_shared<Rook>(Piece::PieceColor::Black, Piece::PieceType::Rook, 5, BoardUtils::CellNameToIndex("h8")));

	pieces.push_back(std::make_shared<Knight>(Piece::PieceColor::Black, Piece::PieceType::Knight, 3, BoardUtils::CellNameToIndex("b8")));
	pieces.push_back(std::make_shared<Knight>(Piece::PieceColor::Black, Piece::PieceType::Knight, 3, BoardUtils::CellNameToIndex("g8")));

	pieces.push_back(std::make_shared<Bishop>(Piece::PieceColor::Black, Piece::PieceType::Bishop, 3, BoardUtils::CellNameToIndex("c8")));
	pieces.push_back(std::make_shared<Bishop>(Piece::PieceColor::Black, Piece::PieceType::Bishop, 3, BoardUtils::CellNameToIndex("f8")));

	pieces.push_back(std::make_shared<Queen>(Piece::PieceColor::Black, Piece::PieceType::Queen, 9, BoardUtils::CellNameToIndex("d8")));
	pieces.push_back(std::make_shared<King>(Piece::PieceColor::Black, Piece::PieceType::King, 100, BoardUtils::CellNameToIndex("e8")));

	for (int i = 0; i < row_width; i++)
	{
		pieces.push_back(std::make_shared<Pawn>(Piece::PieceColor::Black, Piece::PieceType::Pawn, 1, i + 48));
	}

	// set pieces on board
	for (int i = 0; i < pieces.size(); i++)
	{
		(*this)[pieces[i].get()->cellIndex].SetPiece(pieces[i].get());
	}

	kings[0] = (*this)["e1"].GetPiece();
	kings[1] = (*this)["e8"].GetPiece();
}

void Board::CopyBoard(const Board& other)
{

	// clear pieces and cells
	this->NullAllCells();
	this->pieces.clear();

	// deep copy of pieces
	for (int i = 0; i < other.pieces.size(); i++)
	{

		switch (other.pieces[i]->type)
		{
		case Piece::PieceType::Pawn:
			this->pieces.push_back(std::make_shared<Pawn>(*other.pieces[i]));
			break;

		case Piece::PieceType::Bishop:
			this->pieces.push_back(std::make_shared<Bishop>(*other.pieces[i]));
			break;

		case Piece::PieceType::Knight:
			this->pieces.push_back(std::make_shared<Knight>(*other.pieces[i]));
			break;

		case Piece::PieceType::Queen:
			this->pieces.push_back(std::make_shared<Queen>(*other.pieces[i]));
			break;

		case Piece::PieceType::Rook:
			this->pieces.push_back(std::make_shared<Rook>(*other.pieces[i]));
			break;

		case Piece::PieceType::King:
			this->pieces.push_back(std::make_shared<King>(*other.pieces[i]));
			break;

		default:
			break;
		}
	}

	// set pieces on board
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->GetIsCaptured()) continue;
		(*this)[pieces[i]->cellIndex].SetPiece(pieces[i].get());
	}

	kings[0] = (*this)[other.kings[0]->cellIndex].GetPiece();
	kings[1] = (*this)[other.kings[1]->cellIndex].GetPiece();

	playerWhite = other.playerWhite;
	playerBlack = other.playerBlack;
	currentPlayer = (other.currentPlayer == &other.playerWhite) ? &playerWhite : &playerBlack;
}

void Board::NullAllCells()
{	
	for (int i = 0; i < kings.size(); i++)
	{
		kings[i] = nullptr;
	}

	for (int i = 0; i < cells.size(); i++)
	{
		cells[i].SetPiece(nullptr);
	}
}

bool Board::IsCellAttackedByEnemyPiece(int cellIndex, Piece::PieceColor activePieceColor) const
{
	const Cell* cell = &(*this)[cellIndex];

	Piece::PieceColor enemyPieceColor = (activePieceColor == Piece::PieceColor::White) ? Piece::PieceColor::Black : Piece::PieceColor::White;

	int row = cellIndex / 8;
	int column = cellIndex % 8;

	Board tempBoard(*this);
	
	//make a temp piece, so pawns will also attack it
	if (tempBoard[cellIndex].GetPiece() == nullptr)
	{
		tempBoard.pieces.push_back(std::make_shared<Pawn>(activePieceColor, Piece::PieceType::Pawn, 1, cellIndex));
		tempBoard[cellIndex].SetPiece(tempBoard.pieces.back().get());
	}

	//bool isAttackedKing = cells[cellIndex].GetPiece() && cells[cellIndex].GetPiece()->type == Piece::PieceType::King;
	
	//go through every enemy piece and check if they attack cell
	for (int i = 0; i < tempBoard.pieces.size(); i++)
	{
		if (tempBoard.pieces[i]->isCaptured || tempBoard.pieces[i]->color != enemyPieceColor) continue;
		//if (tempBoard.pieces[i]->type == Piece::PieceType::King && isAttackedKing) continue;

		auto validMoves = tempBoard.pieces[i]->GetValidMoves(tempBoard);

		for (int j = 0; j < validMoves.size(); j++)
		{
			if (validMoves[j]->GetToCell() == cellIndex) return true;
		}
	}

	return false;
}

Piece* Board::GetKing(Piece::PieceColor kingColor) const
{
	for (int i = 0; i < kings.size(); i++)
	{
		if (kings[i]->color == kingColor) return kings[i];
	}
	throw std::exception("No king in the kings array");
}

Player& Board::GetPlayer(Piece::PieceColor playerColor)
{
	return (playerColor == Piece::PieceColor::White) ? playerWhite : playerBlack;
}

const Player& Board::GetPlayer(Piece::PieceColor playerColor) const
{
	return (playerColor == Piece::PieceColor::White) ? playerWhite : playerBlack;
}

Player& Board::GetOppositePlayer(Piece::PieceColor playerColor)
{
	return (playerColor == Piece::PieceColor::White) ? playerBlack : playerWhite;
}

const Player& Board::GetOppositePlayer(Piece::PieceColor playerColor) const
{
	return (playerColor == Piece::PieceColor::White) ? playerBlack : playerWhite;
}

void Board::ChangeCurrentPlayer()
{
	currentPlayer = &(this->GetOppositePlayer(currentPlayer->GetColor()));
}

std::shared_ptr<Move> Board::parseMove(int fromCell, int toCell) const
{
	Piece* piece = cells[fromCell].GetPiece();

	if (piece == nullptr) {
		return nullptr;
	}

	// check if castle move
	if (piece->type == Piece::PieceType::King && abs(fromCell - toCell) == 2) {
		return std::make_shared<CastleMove>(fromCell, toCell);
	}

	// check if promotion move or enPassantMove
	if (piece->type == Piece::PieceType::Pawn) {

		int fromCellRow = fromCell / Board::row_width;
		int fromCellCol = fromCell % Board::row_width;

		int toCellRow = toCell / Board::row_width;
		int toCellCol = toCell % Board::row_width;

		int lastRank = (piece->color == Piece::PieceColor::White) ? 7 : 0;
		if (toCellRow == lastRank) {
			return std::make_shared<PromotionMove>(fromCell, toCell, toCell);
		}
		
		int enPassantRank = (piece->color == Piece::PieceColor::White) ? 4 : 3;
		if (fromCellRow == enPassantRank && std::abs(toCellCol - fromCellCol) == 1
			&& cells[toCell].GetPiece() == nullptr) {

			if (piece->color == Piece::PieceColor::White)
			{
				return std::make_shared<EnPassantMove>(fromCell, toCell,
					toCell - 8, Move::MoveType::EnPassant);
			}
			else
			{
				return std::make_shared<EnPassantMove>(fromCell, toCell,
					toCell + 8, Move::MoveType::EnPassant);
			}
		}
	}

	// otherwise it's a normal move
	return std::make_shared<Move>(fromCell, toCell, toCell, Move::MoveType::Move);
}

bool Board::IsCheckMate() const
{
	Piece* enemyKing = this->GetKing(this->GetOppositePlayer(currentPlayer->GetColor()).GetColor());

	if(this->IsCellAttackedByEnemyPiece(enemyKing->cellIndex, enemyKing->color)
		&& MoveValidator::filterValidMoves(enemyKing->GetValidMoves(*this), *this).size() == 0) return true;

	return false;
}

bool Board::IsStaleMate() const
{

	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->color == currentPlayer->GetColor() 
			&& MoveValidator::filterValidMoves(pieces[i]->GetValidMoves(*this), *this).size() != 0) return false;
	}

	return true;
}

bool Board::IsDraw() const
{
	return false;
}

void Board::UpdateCastleVariants(const Move& lastMove)
{
	Cell& lastMoveCell = cells[lastMove.toCell];
	Piece* piece = lastMoveCell.GetPiece();
	Player& player = this->GetPlayer(piece->color);

	if (piece->type == Piece::PieceType::King)
	{
		player.SetCanCastleLong(false);
		player.SetCanCastleShort(false);
	}
	else if(piece->type == Piece::PieceType::Rook)
	{
		if (piece->color == Piece::PieceColor::White)
		{
			if (lastMove.fromCell == 0) player.SetCanCastleLong(false);
			else if (lastMove.fromCell == 7) player.SetCanCastleShort(false);
		}
		else
		{
			if (lastMove.fromCell == 56) player.SetCanCastleLong(false);
			else if (lastMove.fromCell == 63) player.SetCanCastleShort(false);
		}
	}
}

void Board::UpdateEnPassant(const Move& lastMove)
{
	Cell& lastMoveCell = cells[lastMove.toCell];
	Piece* myPiece = lastMoveCell.GetPiece();
	Player& player = this->GetPlayer(myPiece->color);

	for (int i = 0, size = pieces.size(); i < size; i++)
	{
		// set EnPassant to false for every friend Piece
		if (pieces[i]->color == myPiece->color && pieces[i]->type == Piece::PieceType::Pawn)
		{
			Pawn* pawn = dynamic_cast<Pawn*>(pieces[i].get());

			if (pawn != nullptr) pawn->SetEnPassantCell(nullptr);
			else throw std::exception("The piece with pieceType Pawn is not actually Pawn");
		} 
	}


	if (myPiece->type == Piece::PieceType::Pawn && std::abs(lastMove.toCell - lastMove.fromCell) == 16)
	{
		int pawnColumn = lastMove.toCell % Board::row_width;

		if (pawnColumn != 0)
		{
			Piece* enemyPiece = cells[lastMove.toCell - 1].GetPiece();
			if (enemyPiece != nullptr && myPiece->color != enemyPiece->color && enemyPiece->type == Piece::PieceType::Pawn)
			{
				Pawn* pawn = dynamic_cast<Pawn*>(enemyPiece);

				if (pawn != nullptr)
				{
					// white pawn takes
					if (pawn->color == Piece::PieceColor::White)
					{
						pawn->SetEnPassantCell(&cells[lastMove.toCell + 8]);
					}
					else
					{
						pawn->SetEnPassantCell(&cells[lastMove.toCell - 8]);
					}
				}
				else throw std::exception("The piece with pieceType Pawn is not actually Pawn");
			}
		}

		if (pawnColumn != 7)
		{
			Piece* enemyPiece = cells[lastMove.toCell + 1].GetPiece();
			if (enemyPiece != nullptr && myPiece->color != enemyPiece->color && enemyPiece->type == Piece::PieceType::Pawn)
			{
				Pawn* pawn = dynamic_cast<Pawn*>(enemyPiece);

				if (pawn != nullptr)
				{
					// white pawn takes
					if (pawn->color == Piece::PieceColor::White)
					{
						pawn->SetEnPassantCell(&cells[lastMove.toCell + 8]);
					}
					else
					{
						pawn->SetEnPassantCell(&cells[lastMove.toCell - 8]);
					}
				}
				else throw std::exception("The piece with pieceType Pawn is not actually Pawn");
			}
		}

	}
	

}

std::vector<std::shared_ptr<Piece>>& Board::GetPieces()
{
	return pieces;
}

Player* Board::GetCurrentPlayer() const
{
	return this->currentPlayer;
}


