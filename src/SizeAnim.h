#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class SizeAnim : public Animation
{
protected:
    Animation *Clone() const override { return new SizeAnim(*this); }

private:
    sf::RectangleShape *RectShapeObj;
    sf::CircleShape *CircShapeObj;
    sf::Sprite *SpriteObj;

    sf::Vector2f FinalSize;
    sf::Vector2f StartSize;

    void SetObjSize(sf::Vector2f size);
    sf::Vector2f GetObjSize();
    void ToDoAtStart() override;

public:
    void MakeAMove(float UpdatedProgress) override;
    void SetObj(sf::Sprite &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    void SetSize(sf::Vector2f size);
};