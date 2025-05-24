#pragma once
#include "Widget.h"
#include "RoundedRectangleShape.hpp"
#include "Signal.h"
#include "ShapeMaskRenderer.h"

class ProgressBar : public Widget
{
private:
    float minVal = 0;
    float maxVal = 100;
    float currentVal = 0;

    RoundedRectangleShape body;
    RoundedRectangleShape curr;

    mutable ShapeMaskRenderer maskRenderer;
    mutable RoundedRectangleShape maskShape;

    Signal<float> ValueChanged;
    bool useMask = 0;

    sf::Vector2f DefaultSize{150, 30};
    float DefaultOutlineThickness = 2;
    float DefaultCornerRadius = 10;
    sf::Color DefaultBodyFillColor = sf::Color(200, 200, 200, 200);
    sf::Color DefaulProgressFillColor = sf::Color(0, 100, 0);

public:
    ProgressBar();
    ~ProgressBar();

    float GetValue() const { return currentVal; }
    void SetValue(float value);

    sf::Vector2f getSize() const { return getBounds().getSize(); }
    void setSize(sf::Vector2f size);

    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
