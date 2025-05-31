#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include "Signal.h"
#include "RoundedRectangleShape.hpp"


class DropDown;
class Group : public sf::Drawable
{
protected:
    std::vector<sf::Drawable *> drawables;
    std::vector<sf::Text *> Texts;
    std::vector<sf::Sprite *> Sprites;
    std::vector<sf::Shape *> Shapes;
    std::vector<sf::VertexArray *> VertexArrays;
    std::vector<Group *> Groups;

    sf::Vector2f Pos = {0.f, 0.f};
    float Rotation = 0.f;
    sf::Vector2f Scale = {1.f, 1.f};
    sf::Vector2f Origin = {0.f, 0.f};

public:
    sf::Transform getTransform() const;
    // Signals
    Signal<sf::Vector2f> onPositionChanged;
    Signal<float> onRotationChanged;
    Signal<sf::Vector2f> onScaleChanged;
    Signal<sf::Vector2f> onOriginChanged;
    Signal<> onBoundsChanged;

    // ADD
    void add(sf::Text &o);
    void add(sf::Sprite &o);
    void add(sf::RectangleShape &o);
    void add(sf::CircleShape &o);
    void add(sf::Shape *o);
    void add(sf::VertexArray &o);
    void add(Group &o);
    void add(RoundedRectangleShape &o);
    // REMOVE
    void remove(sf::Text &o);
    void remove(sf::Sprite &o);
    void remove(sf::RectangleShape &o);
    void remove(sf::CircleShape &o);
    void remove(sf::Shape *o);
    void remove(sf::VertexArray &o);
    void remove(Group &o);
    void remove(RoundedRectangleShape &o);
    void clear();
    // POS
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void move(sf::Vector2f offset);

    // ROTATION
    float getRotation() const;
    void setRotation(float rotation);
    void rotate(float offset);

    // SCALE
    void setScale(sf::Vector2f scale);
    void scale(sf::Vector2f factor);
    sf::Vector2f getScale() const;

    // ORIGIN
    void SetOrigin(sf::Vector2f origin);
    sf::Vector2f GetOrigin() const;

    // BOUNDS
    sf::FloatRect getBounds() const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    friend DropDown;
};