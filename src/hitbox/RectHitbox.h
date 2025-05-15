#pragma once
#include "Hitbox.h"

class CircleHitbox; // Forward

class RectHitbox : public Hitbox {
public:
    RectHitbox(const sf::Vector2f& pos, const sf::Vector2f& size);

    bool intersects(const Hitbox& other) const override;
    bool contains(const sf::Vector2f& point) const override;

    void setPosition(const sf::Vector2f& pos) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;

    void draw(sf::RenderTarget& target, bool colliding) const override;

private:
    sf::Vector2f position;
    sf::Vector2f size;
};
