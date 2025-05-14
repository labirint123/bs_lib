#pragma once
#include "Hitbox.h"

class RectHitbox; 

class CircleHitbox : public Hitbox {
public:
    CircleHitbox(const sf::Vector2f& pos, float radius);

    bool intersects(const Hitbox& other) const override;
    bool contains(const sf::Vector2f& point) const override;

    void setPosition(const sf::Vector2f& pos) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;

    void draw(sf::RenderTarget& target, bool colliding) const override;
    float getRadius() const;

private:
    sf::Vector2f position;
    float radius;
};
