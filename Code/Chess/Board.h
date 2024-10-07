#pragma once
#include <string>
#include <vector>
#include <memory>
#include <array>
#include "Cell/Cell.h"
#include "Moves/AllMoves.h"
#include "BoardUtils/BoardUtils.h"
#include "Pieces/AllPieces.h"
#include "MoveValidator/MoveValidator.h"
#include "Player/Player.h"

class Board
{

public:

	enum class GameState {
		Running,
		Checkmate,
		Stalemate,
		Draw
	};

	static const int size = 64;
	static const int row_width = 8;
	static const int col_height = 8;
	
	Board();
	Board(const Board& other);

	friend class Cell;
	friend class Piece;
	friend class Pawn;
	friend class MoveValidator;
	friend class Move;
	friend class CastleMove;
	friend class PromotionMove;

	Cell& operator[](const int index);
	Cell& operator[](const std::string& cellName);

	const Cell& operator[](const int index) const;
	const Cell& operator[](const std::string& cellName) const;

	bool Execute(int fromCell, int toCell);

	void ResetBoard();
	void CopyBoard(const Board& other);

	void NullAllCells();

	bool IsCellAttackedByEnemyPiece(int cellIndex, Piece::PieceColor activePieceColor) const;

	Piece* GetKing(Piece::PieceColor kingColor) const;

	Player& GetPlayer(Piece::PieceColor playerColor);
	const Player& GetPlayer(Piece::PieceColor playerColor) const;

	Player& GetOppositePlayer(Piece::PieceColor playerColor);
	const Player& GetOppositePlayer(Piece::PieceColor playerColor) const;
	
	void ChangeCurrentPlayer();

	std::shared_ptr<Move> parseMove(int fromCell, int toCell) const;
	
	bool IsCheckMate() const;
	bool IsStaleMate() const;
	bool IsDraw() const;

	void UpdateCastleVariants(const Move& lastMove);
	void UpdateEnPassant(const Move& lastMove);

	std::vector<std::shared_ptr<Piece>>& GetPieces();

	Player* GetCurrentPlayer() const;

private:

	std::vector<Cell> cells;
	std::vector<std::shared_ptr<Piece>> pieces;
	std::array<Piece*, 2> kings;

	std::vector<std::shared_ptr<Move>> moves;

	Player playerWhite;
	Player playerBlack;
	Player* currentPlayer;
	Player* winnerPlayer = nullptr;

	GameState gameState = GameState::Running;
};

