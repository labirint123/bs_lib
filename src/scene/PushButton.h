#pragma once

#include <SFML/Graphics.hpp>
#include "Signal.h"
#include "Widget.h"
#include "PolygonHitbox.h"
#include "RoundedRectangleShape.hpp"
#include "Utils.hpp"

class PushButton : public Widget {
protected:
    // Visual
    RoundedRectangleShape base;
    sf::Text Text;

    // Logic
    PolygonHitbox* mHitbox = nullptr;
    bool isHovered = false;
    bool isPressed = false;
    bool IsDefaultSignalsEnabled = false;
    void updateHitbox();
    // Style Defaults
    sf::Vector2f DefaultSize{150, 70};
    unsigned int DefaultCharacterSize = 20;
    float DefaultOutlineThickness = 0;
    float DefaultCornerRadius = 10;
    sf::Color DefaultTextColor = sf::Color::Black;
    sf::Color DefaultFillColor = sf::Color(200, 200, 200, 200);

    // Default Behavior IDs
    Signal<>::SlotId onClickDefId;
    Signal<>::SlotId onHoldDefId;
    Signal<>::SlotId onReleaseDefId;
    Signal<>::SlotId onHoveredDefId;

public:
    // Signals
    Signal<bool> onClick;
    Signal<bool> onHold;
    Signal<bool> onRelease;
    Signal<bool> onHovered;

    // Lifecycle
    PushButton();
    ~PushButton();

    // Event Handling
    void HandleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void setDefaultSignalBehavior(bool enable);

    // Styling
    void setSize(sf::Vector2f size);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setTextColor(const sf::Color& color);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setCornerRadius(unsigned int radius);
    void setText(std::string text);

    // Accessors
    sf::Vector2f getSize() const;
    sf::Text GetText() const;
    std::string GetString() const;
    RoundedRectangleShape GetBase() const;
};
