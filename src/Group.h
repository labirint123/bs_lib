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

    sf::Vector2f Pos;
    float Rotation = 0;
    sf::Vector2f Scale  = {1,1};
    sf::Vector2f Origin;

public:
    void add(sf::Text &o);
    void add(sf::Sprite &o);
    void add(sf::RectangleShape &o);
    void add(sf::CircleShape &o);

    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f pos);
    void move(sf::Vector2f offset);
    
    int GetRotation();
    void SetRotation(float rotation);
    void rotate(float offset);

    void SetScale(sf::Vector2f scale);
    void scale(sf::Vector2f scale);
    sf::Vector2f GetScale();
    void SetOrigin(sf::Vector2f origin);
    sf::Vector2f GetOrigin();

    // add size things

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
