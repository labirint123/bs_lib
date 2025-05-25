#include "UsesTransformable.h"

void UsesTransformable::Move(sf::Vector2f offset)
{
    if (tobj != nullptr)
    {
        return tobj->move(offset);
    }
    else if (gobj != nullptr)
    {
        return gobj->move(offset);
    }
}

void UsesTransformable::SetPosition(sf::Vector2f pos)
{
    if (tobj != nullptr)
    {
        return tobj->setPosition(pos);
    }
    else if (gobj != nullptr)
    {
        return gobj->setPosition(pos);
    }
}

void UsesTransformable::Rotate(float offset)
{
    if (tobj != nullptr)
    {
        return tobj->rotate(offset);
    }
    else if (gobj != nullptr)
    {
        return gobj->rotate(offset);
    }
}

void UsesTransformable::SetRotation(float rotation)
{
    if (tobj != nullptr)
    {
        return tobj->setRotation(rotation);
    }
    else if (gobj != nullptr)
    {
        return gobj->setRotation(rotation);
    }
}

void UsesTransformable::Scale(sf::Vector2f offset)
{
    if (tobj != nullptr)
    {
        return tobj->scale(offset);
    }
    else if (gobj != nullptr)
    {
        return gobj->scale(offset);
    }
}

void UsesTransformable::SetScale(sf::Vector2f scale)
{
    if (tobj != nullptr)
    {
        return tobj->setScale(scale);
    }
    else if (gobj != nullptr)
    {
        return gobj->setScale(scale);
    }
}

sf::Vector2f UsesTransformable::GetScale()
{
    if (tobj != nullptr)
    {
        return tobj->getScale();
    }
    else if (gobj != nullptr)
    {
        return gobj->getScale();
    }
    return sf::Vector2f();
}
