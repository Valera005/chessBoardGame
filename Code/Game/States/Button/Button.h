#pragma once
#include <functional>
#include <string>
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Font.hpp"


class Button {
public:

    Button(const sf::Vector2f& position, const std::string& text,
        const sf::Font& font, int characterSize, std::function<void()> onClickFunction);

    void Draw(sf::RenderTarget& target) const;
    void HandleEvent(const sf::Event& eventGame);
    bool IsClicked(const sf::Event& eventGame);
    bool IsHoveredOver(const sf::Vector2f& mousePostion);

    void OnHover(const sf::Event& eventGame);

    std::function<void()> onClickFunction;

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};



