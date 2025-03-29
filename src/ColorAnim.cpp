#include "ColorAnim.h"
void ColorAnim::MakeAMove(float UpdatedProgress)
{
    sf::Color nCol(0, 0, 0);
    if (colordiff.r * UpdatedProgress >= 1)
        nCol.r = colordiff.r * UpdatedProgress;
    if (colordiff.g * UpdatedProgress >= 1)
        nCol.g = colordiff.g * UpdatedProgress;
    if (colordiff.b * UpdatedProgress >= 1)
        nCol.b = colordiff.b * UpdatedProgress;
    if (nCol != sf::Color(0, 0, 0))
    {
        AdjustColor(nCol);
        this->LastProgress = UpdatedProgress;
    }
}
void ColorAnim::AdjustColor(sf::Color color)
{
    if (this->ShapeObj != nullptr)
    {
        if (target == Target::Fill)
        {
            sf::Color base = ShapeObj->getFillColor();
            base.r = std::min(255, base.r + color.r);
            base.g = std::min(255, base.g + color.g);
            base.b = std::min(255, base.b + color.b);
            base.a = std::min(255, base.a + color.a);
            ShapeObj->setFillColor(base);
        }
        else if (target == Target::Outline)
        {
            sf::Color base = ShapeObj->getOutlineColor();
            base.r = std::min(255, base.r + color.r);
            base.g = std::min(255, base.g + color.g);
            base.b = std::min(255, base.b + color.b);
            base.a = std::min(255, base.a + color.a);
            ShapeObj->setOutlineColor(base);
        }
    }
    else if (this->TextObj != nullptr)
    {
        if (target == Target::Fill)
        {
            sf::Color base = TextObj->getFillColor();
            base.r = std::min(255, base.r + color.r);
            base.g = std::min(255, base.g + color.g);
            base.b = std::min(255, base.b + color.b);
            base.a = std::min(255, base.a + color.a);
            TextObj->setFillColor(base);
        }
        else if (target == Target::Outline)
        {
            sf::Color base = TextObj->getOutlineColor();
            base.r = std::min(255, base.r + color.r);
            base.g = std::min(255, base.g + color.g);
            base.b = std::min(255, base.b + color.b);
            base.a = std::min(255, base.a + color.a);
            TextObj->setOutlineColor(base);
        }
    }
    else if (this->ColorObj != nullptr)
    {
        ColorObj->r = std::min(255, ColorObj->r + color.r);
        ColorObj->g = std::min(255, ColorObj->g + color.g);
        ColorObj->b = std::min(255, ColorObj->b + color.b);
        ColorObj->a = std::min(255, ColorObj->a + color.a);
    }
}

void ColorAnim::SetObj(sf::Text &obj)
{
    TextObj = &obj;
    ShapeObj = nullptr;
}

void ColorAnim::SetObj(sf::RectangleShape &obj)
{
    TextObj = nullptr;
    ColorObj = nullptr;
    ShapeObj = &obj;
}

void ColorAnim::SetObj(sf::CircleShape &obj)
{
    TextObj = nullptr;
    ColorObj = nullptr;
    ShapeObj = &obj;
}

void ColorAnim::SetObj(sf::Color &obj)
{
    TextObj = nullptr;
    ShapeObj = nullptr;
    ColorObj = &obj;
}

void ColorAnim::SetColor(const sf::Color &color)
{
    if (this->ShapeObj != nullptr)
    {
        if (target == Target::Fill)
        {
            this->colordiff.r = color.r - ShapeObj->getFillColor().r;
            this->colordiff.g = color.g - ShapeObj->getFillColor().g;
            this->colordiff.b = color.b - ShapeObj->getFillColor().b;
        }
        else if (target == Target::Outline)
        {
            this->colordiff.r = color.r - ShapeObj->getOutlineColor().r;
            this->colordiff.g = color.g - ShapeObj->getOutlineColor().g;
            this->colordiff.b = color.b - ShapeObj->getOutlineColor().b;
        }
    }
    else if (this->TextObj != nullptr)
    {
        if (target == Target::Fill)
        {
            this->colordiff.r = color.r - TextObj->getFillColor().r;
            this->colordiff.g = color.g - TextObj->getFillColor().g;
            this->colordiff.b = color.b - TextObj->getFillColor().b;
        }
        else if (target == Target::Outline)
        {
            this->colordiff.r = color.r - TextObj->getOutlineColor().r;
            this->colordiff.g = color.g - TextObj->getOutlineColor().g;
            this->colordiff.b = color.b - TextObj->getOutlineColor().b;
        }
    }
    else if (this->ColorObj != nullptr)
    {
        this->colordiff.r = color.r - ColorObj->r;
        this->colordiff.g = color.g - ColorObj->g;
        this->colordiff.b = color.b - ColorObj->b;
    }
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
