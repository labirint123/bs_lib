#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

class ScaleAnim : public Animation
{
private:
    void MakeAMove(float UpdatedProgress) override;
    void ToDoAtStart() override;
public:
    void SetObj(sf::Text &obj);
    void SetObj(sf::Sprite &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    void SetScaleOffset(sf::Vector2f ScaleOffset);

private:
    sf::Transformable *obj;
    sf::Vector2f ScaleOffset = {0, 0};
    sf::Vector2f StartScale = {0, 0};

    // SizeAnim();
    // ~SizeAnim();
};