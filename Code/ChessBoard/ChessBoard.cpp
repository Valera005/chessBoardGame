#include "ChessBoard.h"
#include <iostream>
using std::cout, std::endl;

std::vector<ChessBoardCell*> GetAllowedCellsPawn(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{};

	Piece* piece = cell->GetPiece();

	int index = cell->cellIndex;

	int row = index / 8;
	int column = index % 8;

	if (piece->color == Piece::PieceColor::White)
	{
		if (!chessboard[index + 8].isTherePiece())
			answer.push_back(&chessboard[index + 8]);

		if (cell->cellName[1] == '2' && !chessboard[index + 8].isTherePiece() && !chessboard[index + 16].isTherePiece())
			answer.push_back(&chessboard[index + 16]);

		if (column != 0 && chessboard[(row + 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor))
			answer.push_back(&chessboard[(row + 1) * 8 + column - 1]);

		if (column != 7 && chessboard[(row + 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor))
			answer.push_back(&chessboard[(row + 1) * 8 + column + 1]);

		if (piece->isAllowedPassageCapture)
			answer.push_back(piece->passageCaptureCell);
		
	}
	else
	{
		if (!chessboard[index - 8].isTherePiece())
			answer.push_back(&chessboard[index - 8]);

		if (cell->cellName[1] == '7' && !chessboard[index - 8].isTherePiece() && !chessboard[index - 16].isTherePiece())
			answer.push_back(&chessboard[index - 16]);

		if (column != 0 && chessboard[(row - 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor))
			answer.push_back(&chessboard[(row - 1) * 8 + column - 1]);

		if (column != 7 && chessboard[(row - 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor))
			answer.push_back(&chessboard[(row - 1) * 8 + column + 1]);

		if (piece->isAllowedPassageCapture)
			answer.push_back(piece->passageCaptureCell);
	}

	return answer;
}

std::vector<ChessBoardCell*> GetAllowedCellsKnight(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{};

	Piece* piece = cell->GetPiece();

	int index = cell->cellIndex;

	int row = index / 8; // 0 - 7
	int column = index % 8; // 0 - 7


	if (row <= 5)
	{
		if (column <= 6 && !chessboard[(row + 2) * 8 + column + 1].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row + 2) * 8 + column + 1]);
		}

		if (column >= 1 && !chessboard[(row + 2) * 8 + column - 1].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row + 2) * 8 + column - 1]);
		}
	}

	if (row >= 2)
	{
		if (column <= 6 && !chessboard[(row - 2) * 8 + column + 1].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row - 2) * 8 + column + 1]);
		}

		if (column >= 1 && !chessboard[(row - 2) * 8 + column - 1].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row - 2) * 8 + column - 1]);
		}
	}

	if (column <= 5)
	{
		if (row <= 6 && !chessboard[(row + 1) * 8 + column + 2].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row + 1) * 8 + column + 2]);
		}

		if (row >= 1 && !chessboard[(row - 1) * 8 + column + 2].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row - 1) * 8 + column + 2]);
		}
	}

	if (column >= 2)
	{
		if (row <= 6 && !chessboard[(row + 1) * 8 + column - 2].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row + 1) * 8 + column - 2]);
		}

		if (row >= 1 && !chessboard[(row - 1) * 8 + column - 2].isThereFriendPiece(activePieceColor))
		{
			answer.push_back(&chessboard[(row - 1) * 8 + column - 2]);
		}
	}

	return answer;
}


std::vector<ChessBoardCell*> GetAllowedCellsRook(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{};

	Piece* piece = cell->GetPiece();

	int index = cell->cellIndex;

	int row = index / 8; // 0 - 7
	int column = index % 8; // 0 - 7

	int row_temp = row - 1, col_temp = column;

	// we go down
	while (row_temp >= 0 && !chessboard[row_temp * 8 + column].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + column]);
		if (chessboard[row_temp * 8 + column].isThereEnemyPiece(activePieceColor)) break;

		row_temp--;
	}

	// go up
	row_temp = row + 1;
	while (row_temp <= 7 && !chessboard[row_temp * 8 + column].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + column]);
		if (chessboard[row_temp * 8 + column].isThereEnemyPiece(activePieceColor)) break;
		row_temp++;
	}

	// go left
	col_temp = column - 1;
	while (col_temp >= 0 && !chessboard[row * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row * 8 + col_temp]);
		if (chessboard[row * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;
		col_temp--;
	}


	// go right
	col_temp = column + 1;
	while (col_temp <= 7 && !chessboard[row * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row * 8 + col_temp]);
		if (chessboard[row * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;
		col_temp++;
	}

	return answer;
}


std::vector<ChessBoardCell*> GetAllowedCellsBishop(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{};

	Piece* piece = cell->GetPiece();

	int index = cell->cellIndex;

	int row = index / 8; // 0 - 7
	int column = index % 8; // 0 - 7

	int row_temp = row + 1, col_temp = column + 1;

	// we go up right
	while (row_temp <= 7 && col_temp <= 7 && !chessboard[row_temp * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + col_temp]);
		if (chessboard[row_temp * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;

		row_temp++;
		col_temp++;
	}

	row_temp = row + 1, col_temp = column - 1;
	// up left
	while (row_temp <= 7 && col_temp >= 0 && !chessboard[row_temp * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + col_temp]);
		if (chessboard[row_temp * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;

		row_temp++;
		col_temp--;
	}

	row_temp = row - 1, col_temp = column - 1;
	// down left
	while (row_temp >= 0 && col_temp >= 0 && !chessboard[row_temp * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + col_temp]);
		if (chessboard[row_temp * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;

		row_temp--;
		col_temp--;
	}

	row_temp = row - 1, col_temp = column + 1;
	// down right
	while (row_temp >= 0 && col_temp <= 7 && !chessboard[row_temp * 8 + col_temp].isThereFriendPiece(activePieceColor))
	{
		answer.push_back(&chessboard[row_temp * 8 + col_temp]);
		if (chessboard[row_temp * 8 + col_temp].isThereEnemyPiece(activePieceColor)) break;

		row_temp--;
		col_temp++;
	}


	return answer;
}


std::vector<ChessBoardCell*> GetAllowedCellsQueen(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{}, rook_answer, bishop_answer;

	rook_answer = GetAllowedCellsRook(cell, chessboard, activePieceColor);
	bishop_answer = GetAllowedCellsBishop(cell, chessboard, activePieceColor);

	answer.insert(answer.end(), rook_answer.begin(), rook_answer.end());
	answer.insert(answer.end(), bishop_answer.begin(), bishop_answer.end());

	return answer;
}


bool ChessBoard::isCellAttackedByEnemyPiece(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	Piece::PieceColor enemyColor = (activePieceColor == Piece::PieceColor::White) ? Piece::PieceColor::Black : Piece::PieceColor::White;

	std::vector<ChessBoardCell*> answer{};

	int index = cell->cellIndex;

	int row = index / 8;
	int column = index % 8;

	// is attacked by pawn
	if (enemyColor == Piece::PieceColor::White && row != 0)
	{
		if (column != 0 && chessboard[(row - 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::Pawn))
			return true;

		if (column != 7 && chessboard[(row - 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::Pawn))
			return true;
	}

	if (enemyColor == Piece::PieceColor::Black && row != 7)
	{

		if (column != 0 && chessboard[(row + 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::Pawn))
			return true;

		if (column != 7 && chessboard[(row + 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::Pawn))
			return true;
	}


	// is attacked by knight
	std::vector<ChessBoardCell*> cellsKnight = GetAllowedCellsKnight(cell, chessboard, activePieceColor);
	for (int i = 0; i < cellsKnight.size(); i++)
	{
		if (cellsKnight[i]->isThereEnemyPiece(activePieceColor, Piece::PieceType::Knight)) return true;
	}


	// is attacked by bishop or Queen
	std::vector<ChessBoardCell*> cellsBishop = GetAllowedCellsBishop(cell, chessboard, activePieceColor);
	for (int i = 0; i < cellsBishop.size(); i++)
	{
		if (cellsBishop[i]->isThereEnemyPiece(activePieceColor, Piece::PieceType::Bishop)
			|| cellsBishop[i]->isThereEnemyPiece(activePieceColor, Piece::PieceType::Queen)) return true;
	}


	// is attacked by Rook or Queen
	std::vector<ChessBoardCell*> cellsRook = GetAllowedCellsRook(cell, chessboard, activePieceColor);
	for (int i = 0; i < cellsRook.size(); i++)
	{
		if (cellsRook[i]->isThereEnemyPiece(activePieceColor, Piece::PieceType::Rook)
			|| cellsRook[i]->isThereEnemyPiece(activePieceColor, Piece::PieceType::Queen)) return true;
	}


	// is attacked by King
	bool isOnLeft = column == 0, isOnRight = column == 7, isOnTop = row == 7, isOnBottom = row == 0;

	if (!isOnTop)
	{
		// up 
		if (chessboard[(row + 1) * 8 + column].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

		// up left
		if (!isOnLeft && chessboard[(row + 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

		// up right
		if (!isOnRight && chessboard[(row + 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

	}

	if (!isOnBottom)
	{
		// bottom 
		if (chessboard[(row - 1) * 8 + column].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

		// bottom left
		if (!isOnLeft && chessboard[(row - 1) * 8 + column - 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

		// bottom right
		if (!isOnRight && chessboard[(row - 1) * 8 + column + 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

	}

	// right
	if (!isOnRight && chessboard[(row * 8) + column + 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;


	// left
	if (!isOnLeft && chessboard[(row * 8) + column - 1].isThereEnemyPiece(activePieceColor, Piece::PieceType::King)) return true;

	return false;
}

ChessBoardCell* ChessBoard::getKingCell(Piece::PieceColor kingColor)
{
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].GetPiece() != nullptr && cells[i].GetPiece()->type == Piece::PieceType::King && cells[i].GetPiece()->color == kingColor)
			return &cells[i];
	}
}

void ChessBoard::Update(sf::Time deltaTime)
{
	cellRedAnimation.Update(deltaTime);
}

void ChessBoard::SelectCell(ChessBoardCell* cell)
{
	selectedCell = cell;
	ShowGreyCircles(selectedCell);
}

void ChessBoard::DeselectCell()
{
	if (selectedCell == nullptr) return;
	UnshowGreyCircles(selectedCell);
	selectedCell = nullptr;
}

Player* ChessBoard::GetCurrentPlayer(Piece::PieceColor pieceColor)
{
	return (pieceColor == Piece::PieceColor::White) ? &playerWhite : &playerBlack;
}

bool ChessBoard::isCastle(ChessBoardCell* fromCell, ChessBoardCell* toCell)
{
	Piece* piece = fromCell->GetPiece();

	if (piece->type != Piece::PieceType::King) return false;

	int indexFrom = fromCell->cellIndex, indexTo = toCell->cellIndex;

	int rowFrom = indexFrom / 8;
	int columnFrom = indexFrom % 8;

	int rowTo = indexTo / 8;
	int columnTo = indexTo % 8;

	return std::abs(columnFrom - columnTo) == 2;
}

void ChessBoard::HandleCastle(ChessBoardCell* kingFromCell, ChessBoardCell* kingToCell)
{
	Piece* kingPiece = kingFromCell->GetPiece();
	Piece::PieceColor& kingColor = kingPiece->color;

	bool isLongCastle = kingFromCell->cellIndex - kingToCell->cellIndex > 0;
	bool isShortCastle = !isLongCastle;

	ChessBoardCell* rookCell = nullptr;
	ChessBoardCell* newRookCell = nullptr;

	if (isLongCastle)
	{
		rookCell = &(*this)[kingFromCell->cellIndex - 4];
		newRookCell = &(*this)[kingFromCell->cellIndex - 1];
	}
	else
	{
		rookCell = &(*this)[kingFromCell->cellIndex + 3];
		newRookCell = &(*this)[kingFromCell->cellIndex + 1];
	}

	kingToCell->SetPiece(kingFromCell->GetPiece());
	kingFromCell->SetPiece(nullptr);

	newRookCell->SetPiece(rookCell->GetPiece());
	rookCell->SetPiece(nullptr);

	Player* cur_player = GetCurrentPlayer(kingColor);
	cur_player->canCastleLong = false;
	cur_player->canCastleShort = false;
}


void ChessBoard::HandlePromotion(Piece::PieceType newPieceType)
{
	Piece* pawnPiece = promotionCell->GetPiece();
	Player* cur_player = GetCurrentPlayer(pawnPiece->color);

	/*
	int ind = 0;
	for (int i = 0; i < cur_player->pieces.size(); i++)
	{
		if (&(cur_player->pieces[i]) == pawnPiece)
		{
			ind = i;
			break;
		}
	}*/


	switch (newPieceType)
	{

	case Piece::PieceType::Knight:
		cur_player->pieces.push_back(Knight{ this->getPieceRect(pawnPiece->color, newPieceType), pawnPiece->color, promotionCell->cellName, GetAllowedCellsKnight });
		break;
	case Piece::PieceType::Bishop:
		cur_player->pieces.push_back(Bishop{ this->getPieceRect(pawnPiece->color, newPieceType), pawnPiece->color, promotionCell->cellName, GetAllowedCellsBishop });
		break;
	case Piece::PieceType::Rook:
		cur_player->pieces.push_back(Rook{ this->getPieceRect(pawnPiece->color, newPieceType), pawnPiece->color, promotionCell->cellName, GetAllowedCellsRook });
		break;
	case Piece::PieceType::Queen:
		cur_player->pieces.push_back(Queen{ this->getPieceRect(pawnPiece->color, newPieceType), pawnPiece->color, promotionCell->cellName, GetAllowedCellsQueen });
		break;

	default:
		break;
	}

	//cur_player->pieces.erase(cur_player->pieces.begin() + ind);
	pawnPiece->isCaptured = true;

	promotionCell->SetPiece(&(cur_player->pieces[cur_player->pieces.size() - 1]));
	promotionCell = nullptr;
}

void ChessBoard::ErasePiece(Piece* piece)
{
	if (piece == nullptr) return;
	Player* cur_player = GetCurrentPlayer(piece->color);

	int ind = 0;
	for (int i = 0; i < cur_player->pieces.size(); i++)
	{
		if (&(cur_player->pieces[i]) == piece)
		{
			ind = i;
			break;
		}
	}

	cur_player->pieces.erase(cur_player->pieces.begin() + ind);
}

void ChessBoard::ErasePiece(ChessBoardCell* cell)
{
	ErasePiece(cell->GetPiece());
}


bool ChessBoard::checkIfCheckmate(Player* forPlayer)
{
	ChessBoardCell* kingCell = getKingCell(forPlayer->piecesColor);
	Piece* kingPiece = kingCell->GetPiece();
	Piece::PieceColor kingColor = kingPiece->color;

	if (!isCellAttackedByEnemyPiece(kingCell, *this, kingColor))
		return false;

	std::vector<ChessBoardCell*> allowedCellsKing = kingPiece->GetAllowedCellsFunc(kingCell, *this, kingColor);


	for (int j = 0; j < allowedCellsKing.size(); j++)
	{
		ChessBoardCell* cellTo = allowedCellsKing[j];

		cellTo->SetPiece(kingCell->GetPiece());
		kingCell->SetPiece(nullptr);

		if (!isCellAttackedByEnemyPiece(cellTo, *this, kingColor))
		{
			cellTo->Revert();
			kingCell->Revert();
			return false;
		}

		cellTo->Revert();
		kingCell->Revert();
	}


	for (int i = 0; i < forPlayer->pieces.size(); i++)
	{
		Piece* current_piece = &(forPlayer->pieces[forPlayer->pieces.size() - i - 1]);

		if (current_piece->isCaptured) continue;
		if (current_piece->type == Piece::PieceType::King) continue;

		ChessBoardCell* cellFrom = &((*this)[current_piece->cellName]);

		std::vector<ChessBoardCell*> allowedCells = current_piece->
			GetAllowedCellsFunc(cellFrom, *this, kingColor);

		Piece* p_ptr = nullptr;

		for (int j = 0; j < allowedCells.size(); j++)
		{
			ChessBoardCell* cellTo = allowedCells[j];

			bool isPassageCapture = HandlePassageCapture(cellFrom, cellTo, p_ptr);

			if (!isPassageCapture)
			{
				cellTo->SetPiece(cellFrom->GetPiece());
				cellFrom->SetPiece(nullptr);
			}
			
			if (!isCellAttackedByEnemyPiece(kingCell, *this, kingColor))
			{
				if (isPassageCapture) RevertPassageCapture(cellFrom, cellTo);
				else
				{
					cellTo->Revert();
					cellFrom->Revert();
				}
				return false;
			}

			if (isPassageCapture) RevertPassageCapture(cellFrom, cellTo);
			else
			{
				cellTo->Revert();
				cellFrom->Revert();
			}
		}
	}

	isCheckMate = true;
	return true;
}

bool ChessBoard::checkIfPat(Player* forPlayer)
{
	ChessBoardCell* kingCell = getKingCell(forPlayer->piecesColor);
	Piece* kingPiece = kingCell->GetPiece();
	Piece::PieceColor kingColor = kingPiece->color;

	if (isCellAttackedByEnemyPiece(kingCell, *this, kingColor))
		return false;

	std::vector<ChessBoardCell*> allowedCellsKing = kingPiece->GetAllowedCellsFunc(kingCell, *this, kingColor);

	for (int j = 0; j < allowedCellsKing.size(); j++)
	{
		ChessBoardCell* cellTo = allowedCellsKing[j];

		cellTo->SetPiece(kingCell->GetPiece());
		kingCell->SetPiece(nullptr);

		if (!isCellAttackedByEnemyPiece(cellTo, *this, kingColor))
		{
			cellTo->Revert();
			kingCell->Revert();
			return false;
		}

		cellTo->Revert();
		kingCell->Revert();
	}

	for (int i = 0; i < forPlayer->pieces.size(); i++)
	{
		Piece* current_piece = &(forPlayer->pieces[forPlayer->pieces.size() - i - 1]);

		if (current_piece->isCaptured) continue;
		if (current_piece->type == Piece::PieceType::King) continue;

		ChessBoardCell* cellFrom = &((*this)[current_piece->cellName]);

		std::vector<ChessBoardCell*> allowedCells = current_piece->
			GetAllowedCellsFunc(cellFrom, *this, kingColor);

		Piece* p_ptr = nullptr;

		for (int j = 0; j < allowedCells.size(); j++)
		{
			ChessBoardCell* cellTo = allowedCells[j];

			bool isPassageCapture = HandlePassageCapture(cellFrom, cellTo, p_ptr);

			if (!isPassageCapture)
			{
				cellTo->SetPiece(cellFrom->GetPiece());
				cellFrom->SetPiece(nullptr);
			}

			if (!isCellAttackedByEnemyPiece(kingCell, *this, kingColor))
			{
				if (isPassageCapture) RevertPassageCapture(cellFrom, cellTo);
				else
				{
					cellTo->Revert();
					cellFrom->Revert();
				}
				return false;
			}

			if (isPassageCapture) RevertPassageCapture(cellFrom, cellTo);
			else
			{
				cellTo->Revert();
				cellFrom->Revert();
			}
		}
	}

	isPat = true;
	return true;
}

void ChessBoard::checkIfPassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell)
{
	Piece* piece = toCell->GetPiece();

	if (piece->type != Piece::PieceType::Pawn) return;

	if (std::abs(fromCell->cellIndex - toCell->cellIndex) != 16) return;

	if (piece->color == Piece::PieceColor::White)
	{
		int row = toCell->cellIndex / 8;
		int col = toCell->cellIndex % 8;

		Piece* pieceToLeft = (*this)[toCell->cellIndex - 1].GetPiece();
		Piece* pieceToRight = (*this)[toCell->cellIndex + 1].GetPiece();
		if (col != 0 && pieceToLeft != nullptr && pieceToLeft->color == Piece::PieceColor::Black && pieceToLeft->type == Piece::PieceType::Pawn)
		{
			pieceToLeft->isAllowedPassageCapture = true;
			pieceToLeft->passageCaptureCell = &((*this)[toCell->cellIndex - 8]);
		}
		if (col != 7 && pieceToRight != nullptr && pieceToRight->color == Piece::PieceColor::Black && pieceToRight->type == Piece::PieceType::Pawn)
		{
			pieceToRight->isAllowedPassageCapture = true;
			pieceToRight->passageCaptureCell = &((*this)[toCell->cellIndex - 8]);
		}	
	}
	else if (piece->color == Piece::PieceColor::Black)
	{
		int row = toCell->cellIndex / 8;
		int col = toCell->cellIndex % 8;

		Piece* pieceToLeft = (*this)[toCell->cellIndex - 1].GetPiece();
		Piece* pieceToRight = (*this)[toCell->cellIndex + 1].GetPiece();
		if (col != 0 && pieceToLeft != nullptr && pieceToLeft->color == Piece::PieceColor::White && pieceToLeft->type == Piece::PieceType::Pawn)
		{
			pieceToLeft->isAllowedPassageCapture = true;
			pieceToLeft->passageCaptureCell = &((*this)[toCell->cellIndex + 8]);
		}
		if (col != 7 && pieceToRight != nullptr && pieceToRight->color == Piece::PieceColor::White && pieceToRight->type == Piece::PieceType::Pawn)
		{
			pieceToRight->isAllowedPassageCapture = true;
			pieceToRight->passageCaptureCell = &((*this)[toCell->cellIndex + 8]);
		}
	}

}

void ChessBoard::clearPassageCapture(Player* cur_player)
{
	for (int i = 0; i < cur_player->pieces.size(); i++)
	{
		if (cur_player->pieces[i].isCaptured) continue;

		if (cur_player->pieces[i].type == Piece::PieceType::Pawn)
		{
			cur_player->pieces[i].isAllowedPassageCapture = false;
			cur_player->pieces[i].passageCaptureCell = nullptr;
		}
	}
}

bool ChessBoard::HandlePassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell, Piece*& pointedCellPiece)
{
	// check if this PassageCapture
	if (fromCell->GetPiece()->type == Piece::PieceType::Pawn && toCell->GetPiece() == nullptr &&
		(std::abs(toCell->cellIndex - fromCell->cellIndex) == 7 || std::abs(toCell->cellIndex - fromCell->cellIndex) == 9))
	{
		Piece* pawn = fromCell->GetPiece();
		if (pawn->color == Piece::PieceColor::White)
		{
			pointedCellPiece = (*this)[toCell->cellIndex - 8].GetPiece();
			(*this)[toCell->cellIndex - 8].SetPiece(nullptr);
			toCell->SetPiece(fromCell->GetPiece());
			fromCell->SetPiece(nullptr);
		}
		else
		{
			pointedCellPiece = (*this)[toCell->cellIndex + 8].GetPiece();
			(*this)[toCell->cellIndex + 8].SetPiece(nullptr);
			toCell->SetPiece(fromCell->GetPiece());
			fromCell->SetPiece(nullptr);
		}

		return true;
	}
	else return false;
}

bool ChessBoard::RevertPassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell)
{
	Piece* pawn = toCell->GetPiece();
	if (pawn->color == Piece::PieceColor::White)
	{
		(*this)[toCell->cellIndex - 8].Revert();
		toCell->Revert();
		fromCell->Revert();
	}
	else
	{
		(*this)[toCell->cellIndex + 8].Revert();
		toCell->Revert();
		fromCell->Revert();
	}

	return false;
}

void ChessBoard::ShowGreyCircles(ChessBoardCell* cell)
{
	if (cell->GetPiece() == nullptr) return;

	std::vector<ChessBoardCell*> allowedCells = cell->GetPiece()->GetAllowedCellsFunc(cell, *this, cell->GetPiece()->color);

	for (int i = 0; i < allowedCells.size(); i++)
	{
		allowedCells[i]->ShowGreyCircle();
	}
}


void ChessBoard::UnshowGreyCircles(ChessBoardCell* cell)
{
	if (cell->GetPiece() == nullptr) return;

	std::vector<ChessBoardCell*> allowedCells = cell->GetPiece()->GetAllowedCellsFunc(cell, *this, cell->GetPiece()->color);

	for (int i = 0; i < allowedCells.size(); i++)
	{
		allowedCells[i]->UnshowGreyCircle();
	}
}


std::vector<ChessBoardCell*> GetAllowedCellsKing(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor)
{
	std::vector<ChessBoardCell*> answer{};

	Piece* piece = cell->GetPiece();
	Player* cur_player = chessboard.GetCurrentPlayer(activePieceColor);

	int index = cell->cellIndex;

	int row = index / 8; // 0 - 7
	int column = index % 8; // 0 - 7

	bool isOnLeft = column == 0, isOnRight = column == 7, isOnTop = row == 7, isOnBottom = row == 0;


	if (!isOnTop)
	{
		// up 
		if (!chessboard[(row + 1) * 8 + column].isThereFriendPiece(activePieceColor)
			&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row + 1) * 8 + column], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row + 1) * 8 + column]);

		// up left
		if (!isOnLeft && !chessboard[(row + 1) * 8 + column - 1].isThereFriendPiece(activePieceColor)
			&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row + 1) * 8 + column - 1], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row + 1) * 8 + column - 1]);

		// up right
		if (!isOnRight && !chessboard[(row + 1) * 8 + column + 1].isThereFriendPiece(activePieceColor)
			&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row + 1) * 8 + column + 1], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row + 1) * 8 + column + 1]);
	}

	if (!isOnBottom)
	{
		// bottom 
		if (!chessboard[(row - 1) * 8 + column].isThereFriendPiece(activePieceColor)
			&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row - 1) * 8 + column], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row - 1) * 8 + column]);

		// bottom left
		if (!isOnLeft && !chessboard[(row - 1) * 8 + column - 1].isThereFriendPiece(activePieceColor) && !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row - 1) * 8 + column - 1], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row - 1) * 8 + column - 1]);

		// bottom right
		if (!isOnRight && !chessboard[(row - 1) * 8 + column + 1].isThereFriendPiece(activePieceColor) && !chessboard.isCellAttackedByEnemyPiece(&chessboard[(row - 1) * 8 + column + 1], chessboard, activePieceColor))
			answer.push_back(&chessboard[(row - 1) * 8 + column + 1]);
	}

	// right
	if (!isOnRight && !chessboard[row * 8 + column + 1].isThereFriendPiece(activePieceColor)
		&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[row * 8 + column + 1], chessboard, activePieceColor))
		answer.push_back(&chessboard[row * 8 + column + 1]);

	// left
	if (!isOnLeft && !chessboard[row * 8 + column - 1].isThereFriendPiece(activePieceColor)
		&& !chessboard.isCellAttackedByEnemyPiece(&chessboard[row * 8 + column - 1], chessboard, activePieceColor))
		answer.push_back(&chessboard[row * 8 + column - 1]);


	// if king attacked, don't check for castle variants
	if (chessboard.isCellAttackedByEnemyPiece(&chessboard[index], chessboard, activePieceColor)) return answer;

	if (cur_player->canCastleLong)
	{
		bool canCastleLongLocal = true;
		// check for 2 left cells
		for (int i = 1; i < 3; i++)
		{
			if (chessboard[index - i].isTherePiece())
			{
				canCastleLongLocal = false;
				break;
			}
			if (chessboard.isCellAttackedByEnemyPiece(&chessboard[index - i], chessboard, activePieceColor))
			{
				canCastleLongLocal = false;
				break;
			}
		}

		if (canCastleLongLocal)
		{
			answer.push_back(&chessboard[index - 2]);
		}
	}

	if (cur_player->canCastleShort)
	{
		bool canCastleShort = true;
		// check for 2 left cells
		for (int i = 1; i < 3; i++)
		{
			if (chessboard[index + i].isTherePiece())
			{
				canCastleShort = false;
				break;
			}
			if (chessboard.isCellAttackedByEnemyPiece(&chessboard[index + i], chessboard, activePieceColor))
			{
				canCastleShort = false;
				break;
			}
		}

		if (canCastleShort)
		{
			answer.push_back(&chessboard[index + 2]);
		}
	}


	return answer;
}


void ChessBoard::SetBoard()
{
	// clear Players Info
	playerWhite.pieces.clear();
	playerWhite.caprutedPieces.clear();

	playerBlack.pieces.clear();
	playerBlack.caprutedPieces.clear();

	// set up White pieces
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "a1", GetAllowedCellsRook });
	playerWhite.pieces.push_back(Rook{ Configuration::whiteRookRect, Piece::PieceColor::White, "h1", GetAllowedCellsRook });

	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "b1", GetAllowedCellsKnight });
	playerWhite.pieces.push_back(Knight{ Configuration::whiteKnightRect, Piece::PieceColor::White, "g1", GetAllowedCellsKnight });

	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "c1", GetAllowedCellsBishop });
	playerWhite.pieces.push_back(Bishop{ Configuration::whiteBishopRect, Piece::PieceColor::White, "f1", GetAllowedCellsBishop });

	playerWhite.pieces.push_back(Queen{ Configuration::whiteQueenRect, Piece::PieceColor::White, "d1", GetAllowedCellsQueen });
	playerWhite.pieces.push_back(King{ Configuration::whiteKingRect, Piece::PieceColor::White, "e1", GetAllowedCellsKing });

	for (int i = 0; i < 8; i++)
	{
		playerWhite.pieces.push_back(Pawn{ Configuration::whitePawnRect, Piece::PieceColor::White, this->IndexToCellName(8 + i), GetAllowedCellsPawn });
	}

	// set up Black pieces
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "a8", GetAllowedCellsRook });
	playerBlack.pieces.push_back(Rook{ Configuration::blackRookRect, Piece::PieceColor::Black, "h8", GetAllowedCellsRook });

	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "b8", GetAllowedCellsKnight });
	playerBlack.pieces.push_back(Knight{ Configuration::blackKnightRect, Piece::PieceColor::Black, "g8", GetAllowedCellsKnight });

	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "c8", GetAllowedCellsBishop });
	playerBlack.pieces.push_back(Bishop{ Configuration::blackBishopRect, Piece::PieceColor::Black, "f8", GetAllowedCellsBishop });

	playerBlack.pieces.push_back(Queen{ Configuration::blackQueenRect, Piece::PieceColor::Black, "d8", GetAllowedCellsQueen });
	playerBlack.pieces.push_back(King{ Configuration::blackKingRect, Piece::PieceColor::Black, "e8", GetAllowedCellsKing });

	for (int i = 0; i < 8; i++)
	{
		playerBlack.pieces.push_back(Pawn{ Configuration::blackPawnRect, Piece::PieceColor::Black, this->IndexToCellName(48 + i), GetAllowedCellsPawn });
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

ChessBoard::ChessBoard(sf::Vector2u windowSize) : promotionTab(windowSize)
{
	Configuration::InitialiseTextures();

	promotionTab.Initialise(Configuration::chessPiecesTexture);

	cells.reserve(size);

	int width = windowSize.x;
	int height = windowSize.y;

	sf::Vector2i center(width / 2, height / 2);

	sf::Vector2f cellDimensions = ChessBoardCell::getCellDimensions();

	sf::Vector2i leftBottom(center.x - cellDimensions.x * 3.5, center.y + cellDimensions.y * 3.5);

	chessBoardRect = sf::IntRect(center.x - cellDimensions.x * 4,
		center.y - cellDimensions.y * 4, cellDimensions.x * 8, cellDimensions.y * 8);

	for (int i = 0; i < size; i++)
	{
		if (((i % 2) + (int)((i / 8) % 2)) % 2 == 0)
			cells.emplace_back(sf::Vector2f{ (float)leftBottom.x + ((i % 8) * cellDimensions.x), (float)leftBottom.y - ((i / 8) * cellDimensions.y) }, ChessBoardCell::CellColors::Green, i, ChessBoard::IndexToCellName(i));
		else
			cells.emplace_back(sf::Vector2f{ (float)leftBottom.x + ((i % 8) * cellDimensions.x), (float)leftBottom.y - ((i / 8) * cellDimensions.y) }, ChessBoardCell::CellColors::White, i, ChessBoard::IndexToCellName(i));
	}

	SetBoard();
}

void ChessBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::vector<const ChessBoardCell*> cellsToShowGreyCircle;

	for (int i = 0; i < size; i++)
	{
		target.draw(cells[i]);
		if (cells[i].isShowGreyCircle) cellsToShowGreyCircle.push_back(&cells[i]);
	}

	for (int i = 0; i < size; i++)
	{
		Piece* piece = cells[i].GetPiece();
		if (piece != nullptr)
			target.draw(*piece);
	}

	for (int i = 0; i < cellsToShowGreyCircle.size(); i++)
	{
		target.draw(cellsToShowGreyCircle[i]->greyCircle);
	}

	if (selectedCell != nullptr && selectedCell->GetPiece() != nullptr)
		target.draw(*(selectedCell->GetPiece()));

	if (promotionTab.isToShow) target.draw(promotionTab);
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

void ChessBoard::ChangeActivePlayer()
{
	if (activePlayer == &playerWhite) activePlayer = &playerBlack;
	else activePlayer = &playerWhite;
}


void ChessBoard::ProcessMouseMoved(sf::Event::MouseMoveEvent& mousePosition)
{
	int index = GetIndexByCoords({ mousePosition.x, mousePosition.y });

	if (index >= 0 && index <= 63)
	{
		if (this->pointedCell != &cells[index])
		{
			if (this->pointedCell != nullptr) this->pointedCell->UnPointTo();
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
	if (promotionTab.isToShow)
	{
		bool isHit = false;
		Piece::PieceType newPieceType = promotionTab.ProcessMousePressed(mousePosition, isHit);

		if (isHit)
		{
			HandlePromotion(newPieceType);
		}

		return;
	}

	if (pointedCell != nullptr && selectedCell == nullptr && pointedCell->GetPiece() != nullptr
		&& activePlayer->piecesColor == pointedCell->GetPiece()->color)
	{
		this->SelectCell(pointedCell);
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
		bool isMoveCancelled = false;
		UnshowGreyCircles(selectedCell);

		if (pointedCell != nullptr && pointedCell != selectedCell && isAllowedToMoveToCell(selectedCell, pointedCell))
		{

			if (isCastle(selectedCell, pointedCell))
			{
				this->HandleCastle(selectedCell, pointedCell);
				this->DeselectCell();
				return;
			}

			Piece* pointedCellPiece = pointedCell->GetPiece();
			
			bool isPassageCapture = HandlePassageCapture(selectedCell, pointedCell, pointedCellPiece);

			if (!isPassageCapture)
			{
				pointedCell->SetPiece(selectedCell->GetPiece());
				selectedCell->SetPiece(nullptr);
			}
			
			// if king moved to new position, we recheck if this position is attacked and if so, cancel the move
			if (pointedCell->GetPiece()->type == Piece::PieceType::King &&
				isCellAttackedByEnemyPiece(pointedCell, *this, pointedCell->GetPiece()->color))
			{
				if (isPassageCapture) RevertPassageCapture(selectedCell, pointedCell);
				else
				{
					selectedCell->Revert();
					pointedCell->Revert();
				}
				isMoveCancelled = true;
			}
			// if some piece moved but the king is attacked after this move, we need to cancel it
			else if (isCellAttackedByEnemyPiece(getKingCell(pointedCell->GetPiece()->color), *this, pointedCell->GetPiece()->color))
			{
				if (isPassageCapture) RevertPassageCapture(selectedCell, pointedCell);
				else
				{
					selectedCell->Revert();
					pointedCell->Revert();
				}
				isMoveCancelled = true;

				cellRedAnimation.SetCell(getKingCell(selectedCell->GetPiece()->color));
				cellRedAnimation.Start();
			}

			if (!isMoveCancelled)
			{
				//ErasePiece(pointedCellPiece);
				if (pointedCellPiece != nullptr) pointedCellPiece->isCaptured = true;

				checkIfCheckmate((activePlayer == &playerWhite) ? &playerBlack : &playerWhite);
				checkIfPat((activePlayer == &playerWhite) ? &playerBlack : &playerWhite);
				checkIfPassageCapture(selectedCell, pointedCell);
				clearPassageCapture(activePlayer);
				ChangeActivePlayer();
				Piece* cur_piece = pointedCell->GetPiece();

				// check is this promotion
				if (cur_piece->type == Piece::PieceType::Pawn)
				{
					// if white pawn move to 8 row
					if (cur_piece->color == Piece::PieceColor::White && pointedCell->cellName[1] == '8')
					{
						promotionTab.isToShow = true;
						promotionTab.setSpritesForColor(cur_piece->color);
						promotionCell = pointedCell;
					}
					// if black pawn move to 1 row
					else if (cur_piece->color == Piece::PieceColor::Black && pointedCell->cellName[1] == '1')
					{
						promotionTab.isToShow = true;
						promotionTab.setSpritesForColor(cur_piece->color);
						promotionCell = pointedCell;
					}
				}

				// check if some of the sides lost catle
				if (pointedCell->cellName == "a1")
				{
					playerWhite.canCastleLong = false;
				}
				else if (pointedCell->cellName == "h1")
				{
					playerWhite.canCastleShort = false;
				}
				else if (pointedCell->cellName == "a8")
				{
					playerBlack.canCastleLong = false;
				}
				else if (pointedCell->cellName == "h8")
				{
					playerBlack.canCastleShort = false;
				}

				if (cur_piece->type == Piece::PieceType::Rook)
				{
					if (selectedCell->cellName == "a1" && cur_piece->color == Piece::PieceColor::White)
					{
						playerWhite.canCastleLong = false;
					}
					else if (selectedCell->cellName == "h1" && cur_piece->color == Piece::PieceColor::White)
					{
						playerWhite.canCastleShort = false;
					}

					if (selectedCell->cellName == "a8" && cur_piece->color == Piece::PieceColor::Black)
					{
						playerBlack.canCastleLong = false;
					}
					else if (selectedCell->cellName == "h8" && cur_piece->color == Piece::PieceColor::Black)
					{
						playerBlack.canCastleShort = false;
					}
				}
				else if (cur_piece->type == Piece::PieceType::King)
				{
					if (selectedCell->cellName == "e1" && cur_piece->color == Piece::PieceColor::White)
					{
						playerWhite.canCastleLong = false;
						playerWhite.canCastleShort = false;
					}
					else if (selectedCell->cellName == "e8" && cur_piece->color == Piece::PieceColor::Black)
					{
						playerBlack.canCastleLong = false;
						playerBlack.canCastleShort = false;
					}
				}
			}



		}
		else
		{
			selectedCell->SetPiece(selectedCell->GetPiece());
		}

		this->DeselectCell();
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
	std::vector<ChessBoardCell*> allowedCells = temp->GetAllowedCellsFunc(cellFrom, *this, cellFrom->GetPiece()->color);

	for (int i = 0; i < allowedCells.size(); i++)
	{
		if (cellTo == allowedCells[i]) return true;
	}

	return false;
}

sf::IntRect& ChessBoard::getPieceRect(Piece::PieceColor pieceColor, Piece::PieceType pieceType)
{
	if (pieceColor == Piece::PieceColor::White)
	{

		switch (pieceType)
		{
		case Piece::PieceType::Pawn:
			return Configuration::whitePawnRect;

		case Piece::PieceType::Knight:
			return Configuration::whiteKnightRect;

		case Piece::PieceType::Bishop:
			return Configuration::whiteBishopRect;

		case Piece::PieceType::Rook:
			return Configuration::whiteRookRect;

		case Piece::PieceType::Queen:
			return Configuration::whiteQueenRect;

		case Piece::PieceType::King:
			return Configuration::whiteKingRect;

		default:
			return Configuration::whitePawnRect;

		}
	}
	else
	{
		switch (pieceType)
		{
		case Piece::PieceType::Pawn:
			return Configuration::blackPawnRect;

		case Piece::PieceType::Knight:
			return Configuration::blackKnightRect;

		case Piece::PieceType::Bishop:
			return Configuration::blackBishopRect;

		case Piece::PieceType::Rook:
			return Configuration::blackRookRect;

		case Piece::PieceType::Queen:
			return Configuration::blackQueenRect;

		case Piece::PieceType::King:
			return Configuration::blackKingRect;

		default:
			return Configuration::blackPawnRect;
		}
	}
}

bool ChessBoard::GetIsCheckMate()
{
	return isCheckMate;
}

bool ChessBoard::GetIsPat()
{
	return isPat;
}

