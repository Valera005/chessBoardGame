#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../Chess/Pieces/Piece.h"


class PieceDrawable : public sf::Drawable
{
public:
    PieceDrawable(std::shared_ptr<Piece>& piece, sf::Texture& texture, sf::IntRect& textureRect);
    PieceDrawable(const PieceDrawable& other);
    PieceDrawable(PieceDrawable&& other) noexcept;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(const sf::Vector2f& position);
    
    friend class CellDrawable;
    friend class BoardDrawable;

    static PieceDrawable CreatePieceDrawable(std::shared_ptr<Piece>& piece);

private:
    std::weak_ptr<Piece> piecePtr;  // Reference to the logical piece
    sf::Sprite sprite;  // SFML sprite for rendering
};
