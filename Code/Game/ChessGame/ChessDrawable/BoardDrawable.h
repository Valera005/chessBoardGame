#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Chess/Board.h"
#include "./CellDrawable/CellDrawable.h"
#include "./PieceDrawable/PieceDrawable.h"
#include "../Configuration/Configuration.h"
#include "./Animations/CellRedAnimation.h"

class BoardDrawable
{
public:

    BoardDrawable(Board& board, sf::Vector2u windowSize);
    

    void SelectCell(CellDrawable* cell);
    void DeselectCell();

    void HandleEvent(const sf::Event& event);
    void Update(const sf::Time& deltaTime);
    void Draw(sf::RenderTarget& target) const;


    int GetCellIndex(sf::Vector2i mousePosition);

    void ShowGreyCircles(PieceDrawable* piece);
    void HideGreyCircles();

    void NullAllCells();
    void UpdateBoardState();

    void ResetBoard();
private:
    Board& board;
    std::vector<PieceDrawable> piecesDrawable;
    std::vector<CellDrawable> cellsDrawable;

    CellDrawable* pointedCell = nullptr;
    CellDrawable* selectedCell = nullptr;

    sf::IntRect chessBoardRect;
    CellRedAnimation cellAnimation;
    
};

