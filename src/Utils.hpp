#pragma once
#include <SFML/Graphics.hpp>

inline sf::Vector2f GetSize(const sf::Text &text)
{
    auto bounds = text.getLocalBounds();
    return {bounds.size.x, bounds.size.y};
}

enum class Aligns
{
    LeftTop,
    CenterTop,
    RightTop,
    LeftCenter,
    Center,
    RightCenter,
    LeftBottom,
    CenterBottom,
    RightBottom
};

inline void Align(sf::Text &text, Aligns align)
{
    auto bounds = text.getLocalBounds();
    sf::Vector2f origin;

    if (align == Aligns::LeftTop)
        origin = bounds.position;
    else if (align == Aligns::CenterTop)
        origin = {bounds.position.x + bounds.size.x / 2.f, bounds.position.y};
    else if (align == Aligns::RightTop)
        origin = bounds.position + sf::Vector2f(bounds.size.x, 0.f);
    else if (align == Aligns::LeftCenter)
        origin = {bounds.position.x, bounds.position.y + bounds.size.y / 2.f};
    else if (align == Aligns::Center)
        origin = bounds.position + bounds.size / 2.f;
    else if (align == Aligns::RightCenter)
        origin = {bounds.position.x + bounds.size.x, bounds.position.y + bounds.size.y / 2.f};
    else if (align == Aligns::LeftBottom)
        origin = {bounds.position.x, bounds.position.y + bounds.size.y};
    else if (align == Aligns::CenterBottom)
        origin = {bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y};
    else if (align == Aligns::RightBottom)
        origin = bounds.position + bounds.size;

    text.setOrigin(origin);
}

inline void FitTextToWidth(sf::Text &text, float maxWidth)
{
    float scale = maxWidth / text.getLocalBounds().size.x;
    text.setScale({scale, scale});
}

inline sf::Vector2f GetSize(const sf::Sprite &sprite)
{
    return {sprite.getTexture().getSize().x * sprite.getScale().x,
                        sprite.getTexture().getSize().y * sprite.getScale().y};
}
inline sf::Vector2f SetSize(sf::Sprite &sprite, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(sprite);
    sf::Vector2f scale = {size.x / prevSize.x,size.y / prevSize.y};
    sprite.scale(scale);
}


inline void Align(sf::Sprite &sprite, Aligns align)
{
    sf::Vector2f bounds = GetSize(sprite);
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f origin;

    if (align == Aligns::LeftTop)
        origin = pos;
    else if (align == Aligns::CenterTop)
        origin = {pos.x + bounds.x / 2.f, pos.y};
    else if (align == Aligns::RightTop)
        origin = pos + sf::Vector2f(bounds.x, 0.f);
    else if (align == Aligns::LeftCenter)
        origin = {pos.x, pos.y + bounds.y / 2.f};
    else if (align == Aligns::Center)
        origin = pos + bounds / 2.f;
    else if (align == Aligns::RightCenter)
        origin = {pos.x + bounds.x, pos.y + bounds.y / 2.f};
    else if (align == Aligns::LeftBottom)
        origin = {pos.x, pos.y + bounds.y};
    else if (align == Aligns::CenterBottom)
        origin = {pos.x + bounds.x / 2.f, pos.y + bounds.y};
    else if (align == Aligns::RightBottom)
        origin = pos + bounds;

    sprite.setOrigin(origin);
}