#include "CircleHitbox.h"
#include "RectHitbox.h"
#include <cmath>

CircleHitbox::CircleHitbox(const sf::Vector2f& pos, float r) : position(pos), radius(r) {}

bool CircleHitbox::contains(const sf::Vector2f& point) const {
    sf::Vector2f delta = point - position;
    return (delta.x * delta.x + delta.y * delta.y) <= (radius * radius);
}

bool CircleHitbox::intersects(const Hitbox& other) const {
    if (auto* rect = dynamic_cast<const RectHitbox*>(&other)) {
        return rect->intersects(*this); // делегируем
    }

    if (auto* circle = dynamic_cast<const CircleHitbox*>(&other)) {
        float distSq = std::pow(circle->position.x - position.x, 2) +
                       std::pow(circle->position.y - position.y, 2);
        float rSum = circle->radius + radius;
        return distSq <= rSum * rSum;
    }

    return false;
}

void CircleHitbox::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

sf::Vector2f CircleHitbox::getPosition() const {
    return position;
}

sf::FloatRect CircleHitbox::getBounds() const {
    return { position.x - radius, position.y - radius, radius * 2, radius * 2 };
}

float CircleHitbox::getRadius() const {
    return radius;
}

void CircleHitbox::draw(sf::RenderTarget& target, bool colliding) const {
    sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(colliding ? sf::Color::Red : sf::Color::Green);
    shape.setOutlineThickness(2.f);
    target.draw(shape);
}
