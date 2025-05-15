#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <algorithm>

class RoundedRectangleShape : public sf::Shape
{
public:
    explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f),
                                     float radius = 0.f, unsigned int cornerPointCount = 10)
        : m_size(size), m_cornerPointCount(cornerPointCount)
    {
        float clampedRadius = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        m_radii = { clampedRadius, clampedRadius, clampedRadius, clampedRadius };
        update();
    }

    void setSize(const sf::Vector2f& size)
    {
        m_size = size;
        for (auto& r : m_radii)
            r = std::min(r, std::min(m_size.x, m_size.y) / 2.f);
        update();
    }
    
    const sf::Vector2f& getSize() const { return m_size; }

    void setCornerRadius(float radius)
    {
        float clampedRadius = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        m_radii = { clampedRadius, clampedRadius, clampedRadius, clampedRadius };
        update();
    }

    void setTopLeftRadius(float radius)
    {
        m_radii[0] = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        update();
    }
    float getTopLeftRadius() const { return m_radii[0]; }

    void setTopRightRadius(float radius)
    {
        m_radii[1] = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        update();
    }
    float getTopRightRadius() const { return m_radii[1]; }

    void setBottomRightRadius(float radius)
    {
        m_radii[2] = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        update();
    }
    float getBottomRightRadius() const { return m_radii[2]; }

    void setBottomLeftRadius(float radius)
    {
        m_radii[3] = std::min(radius, std::min(m_size.x, m_size.y) / 2.f);
        update();
    }
    float getBottomLeftRadius() const { return m_radii[3]; }

    void setCornerPointCount(unsigned int count)
    {
        m_cornerPointCount = count;
        update();
    }
    unsigned int getCornerPointCount() const { return m_cornerPointCount; }

    virtual std::size_t getPointCount() const override
    {
        return m_cornerPointCount * 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const override
    {
        unsigned int corner = index / m_cornerPointCount;
        unsigned int indexInCorner = index % m_cornerPointCount;
        float deltaAngle = 90.f / (m_cornerPointCount - 1);
        float angle = 0.f;
        sf::Vector2f center;
        switch (corner)
        {
            case 0:
                center = sf::Vector2f(m_radii[0], m_radii[0]);
                angle = 180.f + indexInCorner * deltaAngle;
                break;
            case 1:
                center = sf::Vector2f(m_size.x - m_radii[1], m_radii[1]);
                angle = 270.f + indexInCorner * deltaAngle;
                break;
            case 2:
                center = sf::Vector2f(m_size.x - m_radii[2], m_size.y - m_radii[2]);
                angle = 0.f + indexInCorner * deltaAngle;
                break;
            case 3:
                center = sf::Vector2f(m_radii[3], m_size.y - m_radii[3]);
                angle = 90.f + indexInCorner * deltaAngle;
                break;
        }
        float rad = angle * 3.14159265f / 180.f;
        return sf::Vector2f(center.x + std::cos(rad) * m_radii[corner],
                            center.y + std::sin(rad) * m_radii[corner]);
    }

private:
    sf::Vector2f m_size;
    unsigned int m_cornerPointCount;
    std::array<float, 4> m_radii;
};
