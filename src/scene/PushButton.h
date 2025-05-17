#pragma once
#include <SFML/Graphics.hpp>
#include "Signal.h"
#include "Widget.h"
#include "PolygonHitbox.h"
#include "RoundedRectangleShape.hpp"
#include "Utils.hpp"

class PushButton : public Widget
{
protected:
    //  Logic
    PolygonHitbox *mHitbox = nullptr;

    //  Draw
    RoundedRectangleShape base;
    sf::Text Text;

    //  Default Style
    sf::Vector2f DefaultSize{150, 70};
    unsigned int DefaultCharacterSize = 20;
    float DefaultOutlineThickness = 0;
    sf::Color DefaultTextColor = sf::Color::Black;
    sf::Color DefaultFillColor = sf::Color(200, 200, 200, 200);
    float DefaultCornerRadius = 10;

public:
    //  Signals
    Signal<bool> onClick;
    Signal<bool> onHold;
    Signal<bool> onRelease;
    Signal<bool> onHovered;

    //  Style
    void setFillColor(const sf::Color &color) { base.setFillColor(color); }
    void setOutlineColor(const sf::Color &color) { base.setOutlineColor(color); }
    void setOutlineThickness(float thickness) { base.setOutlineThickness(thickness); }
    void setTextColor(const sf::Color &color) { Text.setFillColor(color); }
    void setFont(const sf::Font &font)
    {
        Text.setFont(font);
        Align(Text, base, Aligns::Center);
    }
    void setCharacterSize(unsigned int size)
    {
        Text.setCharacterSize(size);
        Align(Text, base, Aligns::Center);
    }
    void setCornerRadius(unsigned int radius) { base.setCornerRadius(radius); }
    void setText(std::string text)
    {
        Text.setString(text);
        Align(Text, base, Aligns::Center);
    }
    void setSize(sf::Vector2f size);

    //  Getters
    RoundedRectangleShape GetBase() { return base; }
    sf::Vector2f getSize() { this->getBounds(); }
    sf::Text GetText() { return Text; }
    std::string GetString() { return Text.getString(); }

    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    PushButton();
    ~PushButton();
};