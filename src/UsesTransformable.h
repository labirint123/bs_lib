#pragma once
#include <SFML/Graphics.hpp>


class UsesTransformable {
    protected:
        sf::Transformable* obj = nullptr;
    
    public:
        virtual void SetObj(sf::Text& o)   { obj = &o; }
        virtual void SetObj(sf::Sprite& o) { obj = &o; }
        virtual void SetObj(sf::RectangleShape& o) { obj = &o; }
        virtual void SetObj(sf::CircleShape& o)    { obj = &o; }
    
        sf::Transformable* GetTransformable() const { return obj; }
    };
    