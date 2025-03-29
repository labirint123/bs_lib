#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

class MoveAnim : public Animation
{
public:

    void MakeAMove(float UpdatedProgress) override; 
    void SetMoveOffset(sf::Vector2f offset);
    void SetObj(sf::Text &obj);
    void SetObj(sf::Sprite &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    
private:
    
    sf::Transformable* obj;
    sf::Vector2f moveOffset;
    void move(float x, float y);

public:
    MoveAnim(/* args */);
    ~MoveAnim();
};
