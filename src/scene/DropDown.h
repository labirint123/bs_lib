#pragma once
#include "Widget.h"
#include "RoundedRectangleShape.hpp"

class DropDown : public Widget
{
protected:
    sf::Vector2f DefaultSize{150, 70};
    unsigned int DefaultCharacterSize = 20;
    float DefaultOutlineThickness = 2;
    float DefaultCornerRadius = 10;
    sf::Color DefaultTextColor = sf::Color::White;
    sf::Color DefaultFillColor = sf::Color(50, 50, 50, 200);
    sf::Color DefaultDisabledFillColor = sf::Color(30, 30, 30, 200);
    sf::Color HoverFillColor = sf::Color(70, 70, 70, 200);
    sf::Color PressedFillColor = sf::Color(30, 30, 30, 200);

    RoundedRectangleShape TopBody;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    DropDown();
};