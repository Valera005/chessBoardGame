#include "Board.h"
#include "MoveValidator/MoveValidator.h"

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


Board::MoveExecutionStatus Board::Execute(int fromCell, int toCell)
{
	if (gameState != Board::GameState::Running) throw std::exception("Game has finished");

	auto move = this->parseMove(fromCell, toCell);

	Board::MoveExecutionStatus moveStatus = MoveValidator::isValidMove(*move, *this);

	if (moveStatus != Board::MoveExecutionStatus::Executed) return moveStatus;

	move->execute(*this);

	moves.emplace_back(move);
	this->AddPosition(PositionToString());

	UpdateCastleVariants(*move);

	UpdateEnPassant(*move);

	IsStaleMate();
	IsCheckMate();
	IsDraw();

	ChangeCurrentPlayer();

	return moveStatus;
}


void Board::ResetBoard()
{
	gameState = Board::GameState::Running;
	isFiveTimesRepetition = false;
	this->positions.clear();
	this->moves.clear();
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

	//row_width
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

	currentPlayer = &playerWhite;
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

	//go through every enemy piece and check if they attack cell
	for (int i = 0; i < tempBoard.pieces.size(); i++)
	{
		if (tempBoard.pieces[i]->isCaptured || tempBoard.pieces[i]->color != enemyPieceColor) continue;

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

bool Board::IsCheckMate()
{
	Piece* enemyKing = this->GetKing(this->GetOppositePlayer(currentPlayer->GetColor()).GetColor());

	if (this->IsCellAttackedByEnemyPiece(enemyKing->cellIndex, enemyKing->color)
		&& gameState == GameState::Stalemate)
	{
		winnerPlayer = currentPlayer;
		gameState = GameState::Checkmate;
		return true;
	}

	return false;
}

bool Board::IsStaleMate()
{

	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->color == GetOppositePlayer(currentPlayer->GetColor()).GetColor()
			&& MoveValidator::filterValidMoves(pieces[i]->GetValidMoves(*this), *this).size() != 0) return false;
	}

	gameState = GameState::Stalemate;
	return true;
}

bool Board::IsDraw()
{
	if (isFiveTimesRepetition)
	{
		gameState = GameState::DrawFiveTimesRepetition;
		return true;
	}

	// 50 moves from each side rule check
	if (moves.size() > 100)
	{
		bool isDraw = true;
		for (int size_m = moves.size(), i = size_m - 100; i < size_m; i++)
		{
			if (moves[i]->isCapturedPiece || moves[i]->movedPieceType == Piece::PieceType::Pawn)
			{
				isDraw = false;
				break;
			}
		}

		if (isDraw)
		{
			gameState = GameState::DrawFiftyMoves;
			return true;
		}
	}


	//sufficient material check

	bool isEnoughMaterial = false;
	int whiteBishopWhite = 0, whiteBishopBlack = 0, whiteKnight = 0, whiteRook = 0, whiteQueen = 0, whitePawn = 0;
	int blackBishopWhite = 0, blackBishopBlack = 0, blackKnight = 0, blackRook = 0, blackQueen = 0, blackPawn = 0;

	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->isCaptured) continue;

		if (pieces[i]->color == Piece::PieceColor::White)
		{
			switch (pieces[i]->type)
			{
			case Piece::PieceType::Queen: whiteQueen++; isEnoughMaterial = true; break;
			case Piece::PieceType::Rook: whiteRook++; isEnoughMaterial = true; break;
			case Piece::PieceType::Pawn: whitePawn++; isEnoughMaterial = true; break;
			case Piece::PieceType::Knight: whiteKnight++; break;
			case Piece::PieceType::Bishop:
				if (pieces[i]->cellIndex % 2 + (pieces[i]->cellIndex / row_width) % 2 == 0) whiteBishopBlack++;
				else whiteBishopWhite++;
				break;

			default:
				break;
			}
		}
		else
		{
			switch (pieces[i]->type)
			{
			case Piece::PieceType::Queen: blackQueen++; isEnoughMaterial = true; break;
			case Piece::PieceType::Rook: blackRook++; isEnoughMaterial = true; break;
			case Piece::PieceType::Pawn: blackPawn++; isEnoughMaterial = true; break;
			case Piece::PieceType::Knight: blackKnight++; break;
			case Piece::PieceType::Bishop:
				if (pieces[i]->cellIndex % 2 + (pieces[i]->cellIndex / row_width) % 2 == 0) blackBishopBlack++;
				else blackBishopWhite++;
				break;

			default:
				break;
			}
		}

		if (isEnoughMaterial) return false;
	}

	// now we can assume rook = 0, queen = 0, pawn = 0 both sides
	
	isEnoughMaterial = true;
	//if king vs king
	if (whiteBishopWhite == 0 && whiteBishopBlack == 0 && whiteKnight == 0 &&
		blackBishopWhite == 0 && blackBishopBlack == 0 && blackKnight == 0) isEnoughMaterial = false;

	//if king and bishop vs king
	//White king and bishop vs king
	if ((whiteBishopBlack + whiteBishopWhite == 1 && whiteKnight == 0
		&& (blackBishopWhite == 0 && blackBishopBlack == 0 && blackKnight == 0)) ||
		//Black king and bishop vs king
		(blackBishopBlack + blackBishopWhite == 1 && blackKnight == 0
			&& (whiteBishopWhite == 0 && whiteBishopBlack == 0 && whiteKnight == 0)))
		isEnoughMaterial = false;

	//if king and knight vs king
	if ((whiteBishopBlack + whiteBishopWhite == 0 && whiteKnight == 1
		&& (blackBishopWhite == 0 && blackBishopBlack == 0 && blackKnight == 0)) ||
		(blackBishopBlack + blackBishopWhite == 0 && blackKnight == 1
			&& (whiteBishopWhite == 0 && whiteBishopBlack == 0 && whiteKnight == 0)))
		isEnoughMaterial = false;

	//if king and bishop vs king and bishop of the same color
	if ((whiteBishopBlack == 1 && whiteKnight == 0) && (blackBishopBlack == 1 && blackKnight == 0) ||
		(whiteBishopWhite == 1 && whiteKnight == 0) && (blackBishopWhite == 1 && blackKnight == 0))
		isEnoughMaterial = false;

	if (!isEnoughMaterial) gameState = GameState::DrawInsufficientMaterial;

	return gameState == GameState::Running;
}

void Board::UpdateCastleVariants(const Move& lastMove)
{
	if (!(*this)["e1"].GetPiece() || (*this)["e1"].GetPiece()->GetPieceColor() != Piece::PieceColor::White
		|| (*this)["e1"].GetPiece()->GetPieceType() != Piece::PieceType::King)
	{
		playerWhite.SetCanCastleLong(false);
		playerWhite.SetCanCastleShort(false);
	}
	
	if (!(*this)["a1"].GetPiece() || (*this)["a1"].GetPiece()->GetPieceColor() != Piece::PieceColor::White
		|| (*this)["a1"].GetPiece()->GetPieceType() != Piece::PieceType::Rook) playerWhite.SetCanCastleLong(false);

	if (!(*this)["h1"].GetPiece() || (*this)["h1"].GetPiece()->GetPieceColor() != Piece::PieceColor::White
		|| (*this)["h1"].GetPiece()->GetPieceType() != Piece::PieceType::Rook) playerWhite.SetCanCastleShort(false);


	if (!(*this)["e8"].GetPiece() || (*this)["e8"].GetPiece()->GetPieceColor() != Piece::PieceColor::Black
		|| (*this)["e8"].GetPiece()->GetPieceType() != Piece::PieceType::King)
	{
		playerBlack.SetCanCastleLong(false);
		playerBlack.SetCanCastleShort(false);
	}

	if (!(*this)["a8"].GetPiece() || (*this)["a8"].GetPiece()->GetPieceColor() != Piece::PieceColor::Black
		|| (*this)["a8"].GetPiece()->GetPieceType() != Piece::PieceType::Rook) playerBlack.SetCanCastleLong(false);

	if (!(*this)["h8"].GetPiece() || (*this)["h8"].GetPiece()->GetPieceColor() != Piece::PieceColor::Black
		|| (*this)["h8"].GetPiece()->GetPieceType() != Piece::PieceType::Rook) playerBlack.SetCanCastleShort(false);



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

std::string Board::PositionToString() const
{
	std::string res = "";
	for (int i = 0; i < cells.size(); i++)
	{
		res += BoardUtils::CellToString(cells[i]);
	}

	if (currentPlayer->GetColor() == Piece::PieceColor::White) res += "W";
	else res += "B";

	return res;
}

void Board::AddPosition(const std::string position)
{
	if (positions.find(position) == positions.end()) positions[position] = 1;
	else positions[position] += 1;

	if (positions[position] == 5) isFiveTimesRepetition = true;
}

Board::GameState Board::GetGameState() const
{
	return gameState;
}

const Player* Board::GetWinnerPlayer() const
{
	return winnerPlayer;
}


