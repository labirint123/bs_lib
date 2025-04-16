#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Group : public sf::Drawable
{
protected:
    std::vector<sf::Drawable *> drawables;
    std::vector<sf::Text *> Texts;
    std::vector<sf::Sprite *> Sprites;
    std::vector<sf::Shape *> Shapes;

    sf::Vector2f Pos = {0.f, 0.f};
    float Rotation = 0.f;
    sf::Vector2f Scale = {1.f, 1.f};
    sf::Vector2f Origin = {0.f, 0.f};

    sf::Transform getTransform() const;

public:
    // ADD
    void add(sf::Text &o);
    void add(sf::Sprite &o);
    void add(sf::RectangleShape &o);
    void add(sf::CircleShape &o);

    // POS
    sf::Vector2f GetPosition() const;
    void SetPosition(sf::Vector2f pos);
    void move(sf::Vector2f offset);

    // ROTATION
    float GetRotation() const;
    void SetRotation(float rotation);
    void rotate(float offset);

    // SCALE
    void SetScale(sf::Vector2f scale);
    void scale(sf::Vector2f factor);
    sf::Vector2f GetScale() const;

    // ORIGIN
    void SetOrigin(sf::Vector2f origin);
    sf::Vector2f GetOrigin() const;
    // BOUNDS
    sf::FloatRect Group::getBounds() const;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
