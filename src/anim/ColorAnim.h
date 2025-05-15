#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

class ColorAnim : public Animation
{
public:
    enum Target { Fill, Outline };

    ColorAnim();
    ~ColorAnim();

    void SetObj(sf::Text& obj);
    void SetObj(sf::RectangleShape& obj);
    void SetObj(sf::CircleShape& obj);
    void SetObj(sf::Color& obj);
    void SetColor(const sf::Color& color);
    void SetTarget(Target target);

protected:
    void MakeAMove(float UpdatedProgress) override;
    void ToDoAtStart() override;
    Animation *Clone() const override { return new ColorAnim(*this); }

private:
    void AdjustColor(int r, int g, int b);

    sf::Shape* ShapeObj = nullptr;
    sf::Text* TextObj = nullptr;
    sf::Color* ColorObj = nullptr;

    Target target;
    sf::Color StartColor;
    sf::Color EndColor;

    float diffR = 0.f, diffG = 0.f, diffB = 0.f;
    float prevR = 0.f, prevG = 0.f, prevB = 0.f;
};
