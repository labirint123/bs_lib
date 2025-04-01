#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>

class RotateAnim : public Animation
{
public:

    void MakeAMove(float UpdatedProgress) override; 
    void ToDoAtStart() override;
    void SetRotation(float offset);
    void SetObj(sf::Text &obj);
    void SetObj(sf::Sprite &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    
private:
    
    sf::Transformable* obj;
    float rotateDiff;
};
