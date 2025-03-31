#include "ColorAnim.h"
#include <iostream>

void ColorAnim::MakeAMove(float UpdatedProgress)
{
    float diffprog = UpdatedProgress - LastProgress;
    bool iter = 0;
    sf::Color nCol(0, 0, 0);
    if (std::abs(diffR * diffprog) >= 1)
        iter = 1;
    if (std::abs(diffG * diffprog) >= 1)
        iter = 1;
    if (std::abs(diffB * diffprog) >= 1)
        iter = 1;
    if (iter)
    {
        prevR = diffR * diffprog;
        prevG = diffG * diffprog;
        prevB = diffB * diffprog;
        AdjustColor(diffR * diffprog, diffG * diffprog, diffB * diffprog);
        this->LastProgress = UpdatedProgress;
    }
}
void ColorAnim::AdjustColor(int r, int g, int b)
{
    if (this->ShapeObj != nullptr)
    {
        if (target == Target::Fill)
        {
            sf::Color c;
            c = ShapeObj->getFillColor();
            c.r += r;
            c.g += g;
            c.b += b;
            ShapeObj->setFillColor(c);
        }
        else if (target == Target::Outline)
        {
            sf::Color c = ShapeObj->getOutlineColor();
            c.r += r;
            c.g += g;
            c.b += b;
            ShapeObj->setOutlineColor(c);
        }
    }
    else if (this->TextObj != nullptr)
    {
        if (target == Target::Fill)
        {
            sf::Color c = TextObj->getFillColor();
            c.r += r;
            c.g += g;
            c.b += b;
            TextObj->setFillColor(c);
        }
        else if (target == Target::Outline)
        {
            sf::Color c = TextObj->getOutlineColor();
            c.r += r;
            c.g += g;
            c.b += b;
            TextObj->setOutlineColor(c);
        }
    }
    else if (this->ColorObj != nullptr)
    {
        ColorObj->r += r;
        ColorObj->g += g;
        ColorObj->b += b;
    }
}

void ColorAnim::ToDoAtStart()
{

    if (this->ShapeObj != nullptr)
    {
        if (target == Target::Fill)
        {
            StartColor = ShapeObj->getFillColor();
        }
        else if (target == Target::Outline)
        {
            StartColor = ShapeObj->getOutlineColor();
        }
    }
    else if (this->TextObj != nullptr)
    {
        if (target == Target::Fill)
        {
            StartColor = TextObj->getFillColor();
        }
        else if (target == Target::Outline)
        {
            StartColor = TextObj->getOutlineColor();
        }
    }
    else if (this->ColorObj != nullptr)
    {
        StartColor = *ColorObj;
    }
    diffR = EndColor.r - StartColor.r;
    diffG = EndColor.g - StartColor.g;
    diffB = EndColor.b - StartColor.b;
    prevR = StartColor.r;
    prevG = StartColor.g;
    prevB = StartColor.b;
}

void ColorAnim::SetObj(sf::Text& obj)
{
    TextObj = &obj;
    ShapeObj = nullptr;
    ColorObj = nullptr;
}

void ColorAnim::SetObj(sf::RectangleShape& obj)
{
    TextObj = nullptr;
    ColorObj = nullptr;
    ShapeObj = &obj;
}

void ColorAnim::SetObj(sf::CircleShape& obj)
{
    TextObj = nullptr;
    ColorObj = nullptr;
    ShapeObj = &obj;
}

void ColorAnim::SetObj(sf::Color& obj)
{
    TextObj = nullptr;
    ShapeObj = nullptr;
    ColorObj = &obj;
}

void ColorAnim::SetColor(const sf::Color& color)
{
    EndColor = color;
}

void ColorAnim::SetTarget(Target target)
{
    this->target = target;
}

ColorAnim::ColorAnim()
{
}

ColorAnim::~ColorAnim()
{
}
