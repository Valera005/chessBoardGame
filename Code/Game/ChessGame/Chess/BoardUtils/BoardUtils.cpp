#include "BoardUtils.h"
#include "../Pieces/Piece.h"
#include "../Cell/Cell.h"

int BoardUtils::CellNameToIndex(const std::string& cellName)
{
	if (cellName.length() != 2) throw std::exception("Cell Name size has to be 2 letters length");

	if (cellName[0] >= 'a' && cellName[0] <= 'h' && cellName[1] >= '1' && cellName[1] <= '8')
	{
		return ((cellName[1] - '0' - 1) * 8) + (cellName[0] - 'a'); // row * 8 + column
	}
	else throw std::exception("Bad cell name");
}

std::string BoardUtils::IndexToCellName(int index)
{
	if (index < 0 || index > 63) throw std::exception("Index has to be btw 0-64");

	std::string cellName = "00";

	cellName[0] = (char)(index % 8 + 'a');
	cellName[1] = (char)(index / 8 + '1');

	return cellName;
}

std::string BoardUtils::PieceToString(const Piece& piece)
{

	std::string res = "";

	if (piece.GetPieceColor() == Piece::PieceColor::White) res += "W";
	else res += "B";

	switch (piece.GetPieceType())
	{

	case Piece::PieceType::Pawn:
		res += "P";
		break;

	case Piece::PieceType::Knight:
		res += "N";
		break;

	case Piece::PieceType::Bishop:
		res += "E";
		break;

	case Piece::PieceType::Rook:
		res += "R";
		break;

	case Piece::PieceType::Queen:
		res += "Q";
		break;

	case Piece::PieceType::King:
		res += "K";
		break;
		
	default:
		break;
	}

	return res;
}

std::string BoardUtils::CellToString(const Cell& cell)
{
	std::string res = "";

	if (cell.GetPiece() != nullptr && cell.GetPiece()->GetIsCaptured() == false) res += PieceToString(*cell.GetPiece());
	else res += "O";

	return res;
}
