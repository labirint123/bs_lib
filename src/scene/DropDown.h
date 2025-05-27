#pragma once
#include "Widget.h"
#include "RoundedRectangleShape.hpp"

class DropDown : public Widget
{
protected:
    sf::Vector2f Size{150, 30};
    unsigned int CharacterSize = 20;
    float OutlineThickness = 2;
    float CornerRadius = 10;
    sf::Color TextColor = sf::Color::White;
    sf::Color FillColor = sf::Color(50, 50, 50, 200);
    sf::Color DisabledFillColor = sf::Color(30, 30, 30, 200);
    sf::Color HoverFillColor = sf::Color(70, 70, 70, 200);
    sf::Color PressedFillColor = sf::Color(30, 30, 30, 200);

    sf::Font font;
    sf::Text BodyText;
    RoundedRectangleShape TopBody;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void SetPlaceHolderString(std::string str);
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void setFont(sf::Font font);
    DropDown();
};