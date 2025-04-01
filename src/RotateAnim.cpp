#include "RotateAnim.h"

void RotateAnim::MakeAMove(float UpdatedProgress)
{
    float d = UpdatedProgress - LastProgress;
    obj->rotate(d * rotateDiff);
    LastProgress = UpdatedProgress;
}

void RotateAnim::ToDoAtStart()
{
}

void RotateAnim::SetRotation(float offset)
{
    this->rotateDiff = offset;
}

void RotateAnim::SetObj(sf::Text &obj)
{
    this->obj = &obj;
}

void RotateAnim::SetObj(sf::Sprite &obj)
{
    this->obj = &obj;
}

void RotateAnim::SetObj(sf::RectangleShape &obj)
{
    this->obj = &obj;
}

void RotateAnim::SetObj(sf::CircleShape &obj)
{
    this->obj = &obj;
}
