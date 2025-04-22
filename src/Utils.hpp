#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"
#include "Group.h"

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
    RightBottom,
    Right,
    Left,
    Bottom,
    Top
};
//  GET SIZE

inline sf::Vector2f GetSize(const sf::Shape *shape)
{
    auto lb = shape->getLocalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::RectangleShape &shape)
{
    return shape.getSize();
}
inline sf::Vector2f GetSize(const sf::CircleShape &shape)
{
    auto lb = shape.getLocalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::ConvexShape &shape)
{
    auto lb = shape.getLocalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::Sprite &sprite)
{
    auto lb = sprite.getLocalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::Text &text)
{
    auto lb = text.getLocalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const Group &group)
{
    auto lb = group.getBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const RoundedRectangleShape &rect)
{
    return rect.getSize();
}
template <typename T>
auto GetSize(const T &item)
    -> decltype(item.getSize())
{
    return item.getSize();
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

// ALIGN

inline sf::Vector2f GetAlignedPosition(
    sf::Vector2f targetSize,
    sf::Vector2f targetPosition,
    sf::Vector2f itemSize,
    sf::Vector2f itemPosition,
    Aligns align)
{
    float x = targetPosition.x;
    float y = targetPosition.y;

    switch (align)
    {
    case LeftTop:
        break;
    case CenterTop:
        x += (targetSize.x - itemSize.x) * 0.5f;
        break;
    case RightTop:
        x += targetSize.x - itemSize.x;
        break;
    case LeftCenter:
        y += (targetSize.y - itemSize.y) * 0.5f;
        break;
    case Center:
        x += (targetSize.x - itemSize.x) * 0.5f;
        y += (targetSize.y - itemSize.y) * 0.5f;
        break;
    case RightCenter:
        x += targetSize.x - itemSize.x;
        y += (targetSize.y - itemSize.y) * 0.5f;
        break;
    case LeftBottom:
        y += targetSize.y - itemSize.y;
        break;
    case CenterBottom:
        x += (targetSize.x - itemSize.x) * 0.5f;
        y += targetSize.y - itemSize.y;
        break;
    case RightBottom:
        x += targetSize.x - itemSize.x;
        y += targetSize.y - itemSize.y;
        break;
    case Right:
        x += targetSize.x - itemSize.x;
        y = itemPosition.y;
        break;
    case Left:
        y = itemPosition.y;
        break;
    case Bottom:
        x = itemPosition.x;
        y += targetSize.y - itemSize.y;
        break;
    case Top:
        x = itemPosition.x;
        break;
    }
    return {x, y};
}

inline void Align(Group &item, sf::Vector2f targetSize, sf::Vector2f targetPosition, Aligns Align)
{
    item.SetPosition(GetAlignedPosition(targetSize, targetPosition, item.getBounds().getSize(), item.GetPosition(), Align));
}

template <typename T>
inline void Align(T &item, const sf::Vector2f &targetSize, const sf::Vector2f &targetPosition, Aligns align)
{
    const auto itemSize = GetSize(item);
    const auto itemPos = item.getPosition();
    const auto aligned = GetAlignedPosition(
        targetSize,
        targetPosition,
        itemSize,
        itemPos,
        align);
    item.setPosition(aligned);
}
