#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

class ColorAnim : public Animation
{
public:
    enum Target
    {
        Fill,
        Outline
    };

private:
    void MakeAMove(float UpdatedProgress) override;
    void AdjustColor(sf::Color color);

    sf::Shape *ShapeObj = nullptr;
    sf::Text *TextObj = nullptr;
    sf::Color *ColorObj = nullptr;

    Target target;
    sf::Color colordiff;

public:
    void SetObj(sf::Text &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    void SetObj(sf::Color &obj);

    void SetColor(const sf::Color &color);
    void SetTarget(Target target);

    ColorAnim(/* args */);
    ~ColorAnim();
};
