#include "PushButton.h"
#include "bs.h"

void PushButton::setSize(sf::Vector2f size)
{
    base.setSize(size);
    Align(Text, base, Aligns::Center);
}

PushButton::PushButton()
{
    if (bs::DefaultFont != nullptr)
        this->setFont(*bs::DefaultFont);

    setCharacterSize(DefaultCharacterSize);
    setOutlineThickness(DefaultOutlineThickness);
    setTextColor(DefaultTextColor);
    setFillColor(DefaultFillColor);
    setSize(DefaultSize);
    setCornerRadius(DefaultCornerRadius);
    mHitbox = new PolygonHitbox(GetHitbox(&base));

    add(base);
    add(Text);
}

PushButton::~PushButton()
{
    delete mHitbox;
    mHitbox = nullptr;
}

void PushButton::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
}