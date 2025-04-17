#pragma once
#include <SFML/Graphics.hpp>

enum Aligns
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
//  GET SIZE

inline sf::Vector2f GetSize(const sf::Text &text)
{
    auto bounds = text.getLocalBounds();
    return {bounds.getSize().x, bounds.getSize().y};
}
inline sf::Vector2f GetSize(const sf::Sprite &sprite)
{
    return {sprite.getGlobalBounds().getSize().x * sprite.getScale().x,
            sprite.getGlobalBounds().getSize().y * sprite.getScale().y};
}
inline sf::Vector2f GetSize(const sf::Shape *shape)
{
    
    return {shape->getLocalBounds().getSize().x * shape->getScale().x,
            shape->getLocalBounds().getSize().y * shape->getScale().y};
}

//  SET SIZE

inline sf::Vector2f SetSize(sf::Sprite &sprite, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(sprite);
    sf::Vector2f scale = {size.x / prevSize.x, size.y / prevSize.y};
    sprite.scale(scale);
}
inline sf::Vector2f SetSize(sf::Text &text, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(text);
    sf::Vector2f scale = {size.x / prevSize.x, size.y / prevSize.y};
    text.scale(scale);
}
inline sf::Vector2f SetSize(sf::Shape *shape, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(shape);
    sf::Vector2f scale = {size.x / prevSize.x, size.y / prevSize.y};
    shape->scale(scale);
}
//  TEXT OPERATIONS

inline void FitTextToWidth(sf::Text &text, float maxWidth)
{
    float scale = maxWidth / text.getLocalBounds().getSize().x;
    text.setScale({scale, scale});
}
inline void FitTextToHeight(sf::Text &text, float maxHeight)
{
    float scale = maxHeight / text.getLocalBounds().getSize().y;
    text.setScale({scale, scale});
}

