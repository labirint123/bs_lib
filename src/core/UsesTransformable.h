#pragma once
#include <SFML/Graphics.hpp>
#include "Group.h"

class UsesTransformable
{
protected:
    sf::Transformable *tobj = nullptr;
    Group *gobj = nullptr;

public:
    virtual void SetObj(sf::Text &o)
    {
        tobj = &o;
        gobj = nullptr;
    }
    virtual void SetObj(sf::Sprite &o)
    {
        tobj = &o;
        gobj = nullptr;
    }
    virtual void SetObj(sf::RectangleShape &o)
    {
        tobj = &o;
        gobj = nullptr;
    }
    virtual void SetObj(sf::CircleShape &o)
    {
        tobj = &o;
        gobj = nullptr;
    }
    virtual void SetObj(sf::Transformable *o)
    {
        tobj = o;
        gobj = nullptr;
    }
    virtual void SetObj(Group *o)
    {
        gobj = o;
        tobj = nullptr;
    }
protected:
    sf::Transformable *GetTransformable() const { return tobj; }
    void Move(sf::Vector2f offset);
    void SetPosition(sf::Vector2f pos);
    void Rotate(float offset);
    void SetRotation(float rotation);
    void Scale(sf::Vector2f offset);
    void SetScale(sf::Vector2f scale);
    sf::Vector2f GetScale();
};
