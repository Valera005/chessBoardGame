#include "Queen.h"
#include "../Board.h"
#include "../Cell/Cell.h"

Queen::Queen(PieceColor pieceColor, PieceType pieceType, int value, int cellIndex) : Piece(pieceColor, pieceType, value, cellIndex)
{

}

Queen::Queen(const Piece& other) : Piece(other)
{

}

std::vector<std::shared_ptr<Move>> Queen::GetValidMoves(const Board& chessboard) const
{
	std::vector<std::shared_ptr<Move>> answer{}, rook_answer, bishop_answer;

	rook_answer = Rook(this->color, Piece::PieceType::Rook, 5, this->cellIndex).GetValidMoves(chessboard);
	bishop_answer = Bishop(this->color, Piece::PieceType::Bishop, 3, this->cellIndex).GetValidMoves(chessboard);

	answer.insert(answer.end(), rook_answer.begin(), rook_answer.end());
	answer.insert(answer.end(), bishop_answer.begin(), bishop_answer.end());

	return answer;
}
