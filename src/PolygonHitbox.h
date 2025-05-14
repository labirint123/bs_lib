#pragma once
#include "Hitbox.h"

class PolygonHitbox : public Hitbox {
public:
    PolygonHitbox(const std::vector<sf::Vector2f>& points);

    bool intersects(const Hitbox& other) const override;
    bool contains(const sf::Vector2f& point) const override;

    void setPosition(const sf::Vector2f& pos) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;

    void draw(sf::RenderTarget& target, bool colliding) const override;

private:
    std::vector<sf::Vector2f> vertices;
    sf::Vector2f position;
    sf::FloatRect bounds;

    void updateBounds();
    bool pointInPolygon(const sf::Vector2f& p) const;
    bool linesIntersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2) const;
};
