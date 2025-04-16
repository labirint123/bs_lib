#include "Group.h"

void Group::add(sf::Text &o)
{
    drawables.push_back(&o);
}

void Group::add(sf::Sprite &o)
{
    drawables.push_back(&o);
}

void Group::add(sf::RectangleShape &o)
{
    drawables.push_back(&o);
}

void Group::add(sf::CircleShape &o)
{
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
