#include "Group.h"

void Group::add(sf::Text &o)
{
    Texts.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::Sprite &o)
{
    Sprites.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::RectangleShape &o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::CircleShape &o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

sf::Vector2f Group::GetPosition() const
{
    return Pos;
}

void Group::SetPosition(sf::Vector2f pos)
{
    Pos = pos;
}

void Group::move(sf::Vector2f offset)
{
    Pos += offset;
}

float Group::GetRotation() const
{
    return Rotation;
}

void Group::SetRotation(float rotation)
{
    Rotation = rotation;
}

void Group::rotate(float offset)
{
    Rotation += offset;
}

void Group::SetScale(sf::Vector2f scale)
{
    Scale = scale;
}

void Group::scale(sf::Vector2f factor)
{
    Scale.x *= factor.x;
    Scale.y *= factor.y;
}

sf::Vector2f Group::GetScale() const
{
    return Scale;
}

void Group::SetOrigin(sf::Vector2f origin)
{
    Origin = origin;
}

sf::Vector2f Group::GetOrigin() const
{
    return Origin;
}

sf::Transform Group::getTransform() const
{
    sf::Transform transform;
    transform.translate(Pos);
    transform.rotate(Rotation);
    transform.scale(Scale);
    transform.translate(-Origin);
    return transform;
}

void Group::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (size_t i = 0; i < drawables.size(); i++)
    {
        target.draw(*drawables[i], states);
    }
}


sf::FloatRect Group::getBounds() const {
    sf::FloatRect bounds;
    bool hasBounds = false;

    // Helper lambda to merge a new rectangle into our overall bounds.
    auto mergeBounds = [&](const sf::FloatRect &newBounds) {
        if (!hasBounds) {
            bounds = newBounds;
            hasBounds = true;
        } else {
            float left   = std::min(bounds.left, newBounds.left);
            float top    = std::min(bounds.top, newBounds.top);
            float right  = std::max(bounds.left + bounds.width, newBounds.left + newBounds.width);
            float bottom = std::max(bounds.top + bounds.height, newBounds.top + newBounds.height);
            bounds.left = left;
            bounds.top = top;
            bounds.width = right - left;
            bounds.height = bottom - top;
        }
    };

    // Lambda to compute the transformed bounds for a given drawable.
    auto computeTransformedBounds = [&](const sf::Transformable *obj, const sf::FloatRect &localBounds) -> sf::FloatRect {
        // Combine the group's transform with the object's own transform.
        sf::Transform combinedTransform = getTransform() * obj->getTransform();

        // Transform the four corners of the local bounds.
        sf::Vector2f points[4] = {
            combinedTransform.transformPoint(localBounds.left, localBounds.top),
            combinedTransform.transformPoint(localBounds.left + localBounds.width, localBounds.top),
            combinedTransform.transformPoint(localBounds.left, localBounds.top + localBounds.height),
            combinedTransform.transformPoint(localBounds.left + localBounds.width, localBounds.top + localBounds.height)
        };

        float minX = points[0].x, maxX = points[0].x;
        float minY = points[0].y, maxY = points[0].y;
        for (int i = 1; i < 4; ++i) {
            minX = std::min(minX, points[i].x);
            maxX = std::max(maxX, points[i].x);
            minY = std::min(minY, points[i].y);
            maxY = std::max(maxY, points[i].y);
        }
        return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
    };

    // Process each sf::Text object.
    for (auto text : Texts) {
        sf::FloatRect local = text->getLocalBounds();
        sf::FloatRect transformed = computeTransformedBounds(text, local);
        mergeBounds(transformed);
    }

    // Process each sf::Sprite object.
    for (auto sprite : Sprites) {
        sf::FloatRect local = sprite->getLocalBounds();
        sf::FloatRect transformed = computeTransformedBounds(sprite, local);
        mergeBounds(transformed);
    }

    // Process each sf::Shape object.
    for (auto shape : Shapes) {
        sf::FloatRect local = shape->getLocalBounds();
        sf::FloatRect transformed = computeTransformedBounds(shape, local);
        mergeBounds(transformed);
    }

    // If the group is empty, return an empty rectangle.
    if (!hasBounds)
        return sf::FloatRect();
        
    return bounds;
}
