#include "PolygonHitbox.h"
#include "RectHitbox.h"
#include "CircleHitbox.h"

PolygonHitbox::PolygonHitbox(const std::vector<sf::Vector2f>& points)
    : vertices(points), position(0, 0) {
    updateBounds();
}

void PolygonHitbox::setPosition(const sf::Vector2f& pos) {
    sf::Vector2f delta = pos - position;
    for (auto& v : vertices)
        v += delta;
    position = pos;
    updateBounds();
}

sf::Vector2f PolygonHitbox::getPosition() const {
    return position;
}

sf::FloatRect PolygonHitbox::getBounds() const {
    return bounds;
}

void PolygonHitbox::updateBounds() {
    float minX = vertices[0].x, minY = vertices[0].y;
    float maxX = vertices[0].x, maxY = vertices[0].y;
    for (const auto& v : vertices) {
        minX = std::min(minX, v.x);
        minY = std::min(minY, v.y);
        maxX = std::max(maxX, v.x);
        maxY = std::max(maxY, v.y);
    }
    bounds = { minX, minY, maxX - minX, maxY - minY };
    position = { minX, minY };
}

bool PolygonHitbox::pointInPolygon(const sf::Vector2f& p) const {
    int count = 0;
    for (size_t i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
        const auto& a = vertices[i];
        const auto& b = vertices[j];
        if (((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y + 1e-6f) + a.x)) {
            ++count;
        }
    }
    return count % 2 == 1;
}

bool PolygonHitbox::contains(const sf::Vector2f& point) const {
    return pointInPolygon(point);
}

bool PolygonHitbox::linesIntersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2) const {
    auto cross = [](sf::Vector2f v1, sf::Vector2f v2) {
        return v1.x * v2.y - v1.y * v2.x;
    };

    sf::Vector2f d1 = a2 - a1;
    sf::Vector2f d2 = b2 - b1;
    sf::Vector2f delta = b1 - a1;

    float det = cross(d1, d2);
    if (std::abs(det) < 1e-6f) return false;

    float t = cross(delta, d2) / det;
    float u = cross(delta, d1) / det;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool PolygonHitbox::intersects(const Hitbox& other) const {
    if (!getBounds().intersects(other.getBounds()))
        return false;

    if (auto* circle = dynamic_cast<const CircleHitbox*>(&other)) {
        sf::Vector2f c = circle->getPosition();
        float r = circle->getRadius();

        for (const auto& v : vertices) {
            float dx = v.x - c.x;
            float dy = v.y - c.y;
            if ((dx * dx + dy * dy) <= r * r)
                return true;
        }

        if (contains(c)) return true;
        return false;
    }

    if (auto* rect = dynamic_cast<const RectHitbox*>(&other)) {
        sf::FloatRect r = rect->getBounds();

        for (const auto& v : vertices) {
            if (r.contains(v)) return true;
        }

        sf::Vector2f corners[4] = {
            {r.left, r.top},
            {r.left + r.width, r.top},
            {r.left + r.width, r.top + r.height},
            {r.left, r.top + r.height}
        };

        for (auto& p : corners) {
            if (contains(p)) return true;
        }

        sf::Vector2f rectEdges[4][2] = {
            {corners[0], corners[1]},
            {corners[1], corners[2]},
            {corners[2], corners[3]},
            {corners[3], corners[0]}
        };

        for (size_t i = 0; i < vertices.size(); ++i) {
            sf::Vector2f a = vertices[i];
            sf::Vector2f b = vertices[(i + 1) % vertices.size()];
            for (int j = 0; j < 4; ++j) {
                if (linesIntersect(a, b, rectEdges[j][0], rectEdges[j][1]))
                    return true;
            }
        }

        return false;
    }

    return getBounds().intersects(other.getBounds());
}

void PolygonHitbox::draw(sf::RenderTarget& target, bool colliding) const {
    if (vertices.size() < 3) return;

    sf::ConvexShape shape;
    shape.setPointCount(vertices.size());
    for (size_t i = 0; i < vertices.size(); ++i)
        shape.setPoint(i, vertices[i]);

    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(colliding ? sf::Color::Red : sf::Color::Green);
    shape.setOutlineThickness(2.f);
    target.draw(shape);
}
