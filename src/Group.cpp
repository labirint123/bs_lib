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

sf::Vector2f Group::GetPosition()
{
    return Pos;
}

void Group::SetPosition(sf::Vector2f pos)
{
    sf::Vector2f spos = GetPosition();
    move(pos - spos);
}

void Group::move(sf::Vector2f offset)
{
    for (size_t i = 0; i < Shapes.size(); i++)
    {
        Shapes[i]->move(offset);
    }
    for (size_t i = 0; i < Sprites.size(); i++)
    {
        Sprites[i]->move(offset);
    }
    for (size_t i = 0; i < Texts.size(); i++)
    {
        Texts[i]->move(offset);
    }
    this->Pos += offset;
    this->Origin += offset;
}

int Group::GetRotation()
{
    return this->Rotation;
}

void Group::SetRotation(float rotation)
{
    rotate(rotation - this->Rotation);

}

void Group::rotate(float offset)
{
    for (size_t i = 0; i < Shapes.size(); i++)
    {
        Shapes[i]->rotate(offset);
    }
    for (size_t i = 0; i < Sprites.size(); i++)
    {
        Sprites[i]->rotate(offset);
    }
    for (size_t i = 0; i < Texts.size(); i++)
    {
        Texts[i]->rotate(offset);
    }
    this->Rotation += offset;
}

void Group::SetScale(sf::Vector2f scale)
{
    this->scale(scale - this->Scale);
}

void Group::scale(sf::Vector2f scale)
{
    for (size_t i = 0; i < Shapes.size(); i++)
    {
        Shapes[i]->setOrigin(Origin);
        Shapes[i]->scale(scale);
    }
    for (size_t i = 0; i < Sprites.size(); i++)
    {
        Sprites[i]->setOrigin(Origin);
        Sprites[i]->scale(scale);
    }
    for (size_t i = 0; i < Texts.size(); i++)
    {
        Texts[i]->setOrigin(Origin);
        Texts[i]->scale(scale);
    }
}

sf::Vector2f Group::GetScale()
{
    return this->Scale;
}

void Group::SetOrigin(sf::Vector2f origin)
{
    this->Origin = origin;
}

sf::Vector2f Group::GetOrigin()
{
    return Origin;
}

void Group::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (size_t i = 0; i < drawables.size(); i++)
    {
        target.draw(*drawables[i], states);
    }
}
