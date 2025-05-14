#include "RectHitbox.h"
#include "CircleHitbox.h"
#include <algorithm>

RectHitbox::RectHitbox(const sf::Vector2f& pos, const sf::Vector2f& s) : position(pos), size(s) {}

bool RectHitbox::contains(const sf::Vector2f& point) const {
    return getBounds().contains(point);
}

bool RectHitbox::intersects(const Hitbox& other) const {
    if (auto* rect = dynamic_cast<const RectHitbox*>(&other)) {
        return getBounds().intersects(rect->getBounds());
    }

    if (auto* circle = dynamic_cast<const CircleHitbox*>(&other)) {
        sf::FloatRect r = getBounds();
        sf::Vector2f c = circle->getPosition();
        float rad = circle->getRadius();

        float nearestX = std::clamp(c.x, r.left, r.left + r.width);
        float nearestY = std::clamp(c.y, r.top, r.top + r.height);

        float dx = c.x - nearestX;
        float dy = c.y - nearestY;
        return (dx * dx + dy * dy) <= (rad * rad);
    }

    return false;
}

void RectHitbox::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

sf::Vector2f RectHitbox::getPosition() const {
    return position;
}

sf::FloatRect RectHitbox::getBounds() const {
    return { position, size };
}

void RectHitbox::draw(sf::RenderTarget& target, bool colliding) const {
    sf::RectangleShape shape(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(colliding ? sf::Color::Red : sf::Color::Green);
    shape.setOutlineThickness(2.f);
    target.draw(shape);
}
