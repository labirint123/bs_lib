#include "ColorAnim.h"
#include <algorithm>
#include <cmath>

ColorAnim::ColorAnim() {}
ColorAnim::~ColorAnim() {}

void ColorAnim::MakeAMove(float UpdatedProgress)
{
    float curR = diffR * UpdatedProgress;
    float curG = diffG * UpdatedProgress;
    float curB = diffB * UpdatedProgress;

    int deltaR = static_cast<int>(std::round(curR - prevR));
    int deltaG = static_cast<int>(std::round(curG - prevG));
    int deltaB = static_cast<int>(std::round(curB - prevB));

    if (deltaR != 0 || deltaG != 0 || deltaB != 0)
    {
        AdjustColor(deltaR, deltaG, deltaB);
        prevR += deltaR;
        prevG += deltaG;
        prevB += deltaB;
    }

    LastProgress = UpdatedProgress;
}

void ColorAnim::AdjustColor(int r, int g, int b)
{
    auto clamp = [](int value) {
        return static_cast<sf::Uint8>(std::clamp(value, 0, 255));
    };

    if (ShapeObj)
    {
        if (target == Fill)
        {
            sf::Color c = ShapeObj->getFillColor();
            c.r = clamp(c.r + r);
            c.g = clamp(c.g + g);
            c.b = clamp(c.b + b);
            ShapeObj->setFillColor(c);
        }
        else
        {
            sf::Color c = ShapeObj->getOutlineColor();
            c.r = clamp(c.r + r);
            c.g = clamp(c.g + g);
            c.b = clamp(c.b + b);
            ShapeObj->setOutlineColor(c);
        }
    }
    else if (TextObj)
    {
        if (target == Fill)
        {
            sf::Color c = TextObj->getFillColor();
            c.r = clamp(c.r + r);
            c.g = clamp(c.g + g);
            c.b = clamp(c.b + b);
            TextObj->setFillColor(c);
        }
        else
        {
            sf::Color c = TextObj->getOutlineColor();
            c.r = clamp(c.r + r);
            c.g = clamp(c.g + g);
            c.b = clamp(c.b + b);
            TextObj->setOutlineColor(c);
        }
    }
    else if (ColorObj)
    {
        ColorObj->r = clamp(ColorObj->r + r);
        ColorObj->g = clamp(ColorObj->g + g);
        ColorObj->b = clamp(ColorObj->b + b);
    }
}

void ColorAnim::ToDoAtStart()
{
    if (ShapeObj)
    {
        StartColor = (target == Fill) ? ShapeObj->getFillColor()
                                      : ShapeObj->getOutlineColor();
    }
    else if (TextObj)
    {
        StartColor = (target == Fill) ? TextObj->getFillColor()
                                      : TextObj->getOutlineColor();
    }
    else if (ColorObj)
    {
        StartColor = *ColorObj;
    }

    diffR = static_cast<float>(EndColor.r - StartColor.r);
    diffG = static_cast<float>(EndColor.g - StartColor.g);
    diffB = static_cast<float>(EndColor.b - StartColor.b);

    prevR = prevG = prevB = 0.f;
}

void ColorAnim::SetObj(sf::Text& obj)
{
    TextObj = &obj;
    ShapeObj = nullptr;
    ColorObj = nullptr;
}

void ColorAnim::SetObj(sf::RectangleShape& obj)
{
    ShapeObj = &obj;
    TextObj = nullptr;
    ColorObj = nullptr;
}

void ColorAnim::SetObj(sf::CircleShape& obj)
{
    ShapeObj = &obj;
    TextObj = nullptr;
    ColorObj = nullptr;
}

void ColorAnim::SetObj(sf::Color& obj)
{
    ColorObj = &obj;
    ShapeObj = nullptr;
    TextObj = nullptr;
}

void ColorAnim::SetColor(const sf::Color& color)
{
    EndColor = color;
}

void ColorAnim::SetTarget(Target t)
{
    target = t;
}
