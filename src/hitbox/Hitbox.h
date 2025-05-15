#pragma once
#include <SFML/Graphics.hpp>

class Hitbox {
public:
    virtual ~Hitbox() = default;

    virtual bool intersects(const Hitbox& other) const = 0;
    virtual bool contains(const sf::Vector2f& point) const = 0;

    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getBounds() const = 0;

    virtual void draw(sf::RenderTarget& target, bool colliding) const = 0;
};
