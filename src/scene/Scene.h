#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include "Group.h"

class Scene : public sf::Drawable
{
protected:
    std::vector<sf::Drawable *> drawables;
    std::vector<sf::Text *> Texts;
    std::vector<sf::Sprite *> Sprites;
    std::vector<sf::Shape *> Shapes;
    std::vector<sf::VertexArray *> VertexArrays;
    std::vector<Group *> Groups;
    sf::View DefaultView;
public:
    void add(sf::Text &o);
    void add(sf::Sprite &o);
    void add(sf::RectangleShape &o);
    void add(sf::CircleShape &o);
    void add(sf::Shape *o);
    void add(sf::VertexArray &o);
    void add(Group &o);
    virtual void Resize(sf::Vector2f NewSize) = 0;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
