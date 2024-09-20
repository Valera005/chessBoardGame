#pragma once
#include "ChessPieces/AllPieces.h"
#include "ChessBoardCell/ChessBoardCell.h"
#include "../Animations/CellReadAnimation.h"
#include "./GreyCircles/GreyCircle.h"
#include "./PromotionTab/PromotionTab.h"
#include "SFML/Window/Event.hpp"
#include "Player/Player.h"
#include <array>

class ChessBoard : public sf::Drawable
{
	std::vector<ChessBoardCell> cells;
	const int static size = 64;

	ChessBoardCell* pointedCell = nullptr;
	ChessBoardCell* selectedCell = nullptr;
	ChessBoardCell* promotionCell = nullptr;

	Player playerWhite{ Piece::PieceColor::White };
	Player playerBlack{ Piece::PieceColor::Black };

	Player* activePlayer = &playerWhite;

	int turn = 0;
	bool isWhiteMoves = true;
	bool isCheck = false;
	bool isCheckMate = false;
	bool isPat = false;

	CellReadAnimation cellRedAnimation;

	Configuration::GameStates gameStates = Configuration::GameStates::Menu;

	PromotionTab promotionTab;

	void SetBoard();

public:

	ChessBoard(sf::Vector2u windowSize);
	
	enum class CastleVariants {
		Short,
		Long
	};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	static int CellNameToIndex(const std::string& cellName);
	static std::string IndexToCellName(int index);

	ChessBoardCell& operator[](const std::string& cellName);
	ChessBoardCell& operator[](const int& index);

	void ChangeActivePlayer();

	void ShowGreyCircles(ChessBoardCell* cell);
	void UnshowGreyCircles(ChessBoardCell* cell);

	void ProcessMouseMoved(sf::Event::MouseMoveEvent& mousePosition);

	void ProcessMousePressed(sf::Vector2i mousePosition);

	void ProcessMouseReleased(sf::Vector2i mousePosition);

	int GetIndexByCoords(const sf::Vector2i coords);

	sf::IntRect chessBoardRect;

	bool isAllowedToMoveToCell(ChessBoardCell* cellFrom, ChessBoardCell* cellTo);

	bool isCellAttackedByEnemyPiece(ChessBoardCell* cell, ChessBoard& chessboard, Piece::PieceColor activePieceColor);

	ChessBoardCell* getKingCell(Piece::PieceColor kingColor);

	void Update(sf::Time deltaTime);
	
	void SelectCell(ChessBoardCell* cell);
	void DeselectCell();

	Player* GetCurrentPlayer(Piece::PieceColor pieceColor);
	
	bool isCastle(ChessBoardCell* fromCell, ChessBoardCell* toCell);
	void HandleCastle(ChessBoardCell* kingFromCell, ChessBoardCell* kingToCell);
	void HandlePromotion(Piece::PieceType newPieceType);

	void ErasePiece(Piece* piece);
	void ErasePiece(ChessBoardCell* cell);

	bool checkIfCheckmate(Player* forPlayer);
	bool checkIfPat(Player* forPlayer);


	void checkIfPassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell);
	void clearPassageCapture(Player* cur_player);
	bool HandlePassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell, Piece*& pointedCellPiece);
	bool RevertPassageCapture(ChessBoardCell* fromCell, ChessBoardCell* toCell);

	sf::IntRect& getPieceRect(Piece::PieceColor pieceColor, Piece::PieceType pieceType);

	bool GetIsCheckMate();
	bool GetIsPat();
};

