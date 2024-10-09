#include "./Button.h"

Button::Button(const sf::Vector2f& position, const std::string& text, const sf::Font& font,
    int characterSize, std::function<void()> onClickFunction): onClickFunction(onClickFunction)
{
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(characterSize);

    sf::Vector2f buttonTextSize = buttonText.getLocalBounds().getSize();

    buttonText.setOrigin(buttonTextSize.x / 2, buttonTextSize.y / 2);

    buttonShape.setSize(sf::Vector2f(buttonTextSize.x * 1.75, buttonTextSize.y * 1.8));
    buttonShape.setOrigin(buttonShape.getSize().x / 2, buttonShape.getSize().y / 2);
    buttonShape.setFillColor(sf::Color::Black);
    buttonShape.setOutlineThickness(3);
    buttonShape.setOutlineColor(sf::Color::White);
    buttonShape.setPosition(position);

    sf::FloatRect buttonShapeCoords = buttonShape.getGlobalBounds();
    buttonText.setPosition(buttonShapeCoords.left + buttonShapeCoords.width / 2, buttonShapeCoords.top + buttonTextSize.y * 0.7);

    // Center text in button
    //sf::FloatRect textRect = buttonText.getLocalBounds();
    //buttonText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    //buttonText.setPosition(buttonShape.getPosition().x + size.x / 2.0f, buttonShape.getPosition().y + size.y / 2.0f);
}


void Button::Draw(sf::RenderTarget& target) const {
    target.draw(buttonShape);
    target.draw(buttonText);
}


bool Button::IsClicked(const sf::Event& eventGame)
{
    return (eventGame.type == sf::Event::MouseButtonReleased) &&
        eventGame.mouseButton.button == sf::Mouse::Left &&
        buttonShape.getGlobalBounds().contains(eventGame.mouseButton.x, eventGame.mouseButton.y);
}


bool Button::IsHoveredOver(const sf::Vector2f& mousePostion)
{
    return buttonShape.getGlobalBounds().contains(mousePostion);;
}


void Button::OnHover(const sf::Event& eventGame)
{
    if (this->IsHoveredOver(sf::Vector2f(eventGame.mouseMove.x, eventGame.mouseMove.y)))
    {
        this->buttonShape.setOutlineColor(sf::Color::Blue);
    }
    else
    {
        this->buttonShape.setOutlineColor(sf::Color::White);
    }

}


void Button::HandleEvent(const sf::Event& eventGame) {

    switch (eventGame.type)
    {

    case sf::Event::MouseMoved:
        this->OnHover(eventGame);
        break;

    case sf::Event::MouseButtonReleased:
        if (this->IsClicked(eventGame)) this->onClickFunction();
        break;

    default:
        break;
    }
}