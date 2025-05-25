#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"
#include "Group.h"
#include "PolygonHitbox.h"

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
    auto lb = shape->getGlobalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::RectangleShape &shape)
{
    return shape.getSize();
}
inline sf::Vector2f GetSize(const sf::CircleShape &shape)
{
    auto lb = shape.getGlobalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::ConvexShape &shape)
{
    auto lb = shape.getGlobalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::Sprite &sprite)
{
    auto lb = sprite.getGlobalBounds();
    return {lb.width, lb.height};
}
inline sf::Vector2f GetSize(const sf::Text &text)
{
    auto lb = text.getGlobalBounds();
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
inline sf::Vector2f GetSize(const sf::RenderWindow &win)
{
    return {(float)win.getSize().x, (float)win.getSize().y};
}
template <typename T>
auto GetSize(const T &item)
    -> decltype(item.getSize())
{
    return item.getSize();
}

//  SET SIZE

inline void SetSize(sf::Sprite &sprite, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(sprite);
    sf::Vector2f scale = {size.x / prevSize.x, size.y / prevSize.y};
    sprite.scale(scale);
}
inline void SetSize(sf::Text &text, sf::Vector2f size)
{
    sf::Vector2f prevSize = GetSize(text);
    sf::Vector2f scale = {size.x / prevSize.x, size.y / prevSize.y};
    text.scale(scale);
}
inline void SetSize(sf::Shape *shape, sf::Vector2f size)
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
    item.setPosition(GetAlignedPosition(targetSize, targetPosition, item.getBounds().getSize(), item.getPosition(), Align));
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

template <typename T>
inline void Align(T &item, const sf::RenderWindow &win, Aligns align)
{
    const auto itemSize = GetSize(item);
    const auto itemPos = item.getPosition();
    const auto aligned = GetAlignedPosition(
        GetSize(win),
        {0.f, 0.f},
        itemSize,
        itemPos,
        align);
    item.setPosition(aligned);
}

template <
    typename ItemT,
    typename TargetT>
inline void Align(ItemT &item, const TargetT &target, Aligns align)
{
    sf::Vector2f itemSize;
    sf::Vector2f offset{0.f, 0.f};

    if constexpr (std::is_same_v<ItemT, sf::Text>)
    {
        auto bounds = item.getLocalBounds();
        itemSize = {bounds.width, bounds.height};
        offset = {bounds.left, bounds.top};
    }
    else
    {
        itemSize = GetSize(item);
    }

    const auto itemPos = item.getPosition();
    const auto targetSize = GetSize(target);
    const auto targetPosition = target.getPosition();
    const auto aligned = GetAlignedPosition(
        targetSize,
        targetPosition,
        itemSize,
        itemPos,
        align);

    item.setPosition(aligned - offset);
}

inline PolygonHitbox GetHitbox(sf::Shape *shape)
{
    std::vector<sf::Vector2f> globalPoints;

    const sf::Transform &transform = shape->getTransform();
    std::size_t count = shape->getPointCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        sf::Vector2f local = shape->getPoint(i);
        sf::Vector2f global = transform.transformPoint(local);
        globalPoints.push_back(global);
    }

    return PolygonHitbox(globalPoints);
}

inline std::vector<sf::Vector2f> GetTransformedPoints(const sf::Shape *shape, const sf::Transform &transform)
{
    std::vector<sf::Vector2f> points;
    if (!shape)
        return points;

    std::size_t count = shape->getPointCount();
    points.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        sf::Vector2f pt = transform.transformPoint(shape->getPoint(i));
        points.push_back(pt);
    }

    return points;
}
