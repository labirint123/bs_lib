#include "MoveAnim.h"
#include <iostream>

void MoveAnim::MakeAMove(float UpdatedProgress)
{
    float diffP = UpdatedProgress - this->LastProgress;

    sf::Vector2f totalMove = moveOffset * UpdatedProgress;
    sf::Vector2f prevMove = moveOffset * this->LastProgress;
    sf::Vector2f delta = totalMove - prevMove;

    if (std::abs(delta.x) >= 0.5f || std::abs(delta.y) >= 1.5f)
    {
        this->move(delta.x, delta.y);
        this->LastProgress = UpdatedProgress;
    }
    
}

void MoveAnim::ToDoAtStart()
{
    
}

void MoveAnim::SetMoveOffset(sf::Vector2f offset)
{
    this->moveOffset = offset;
}

void MoveAnim::SetObj(sf::Text &obj)
{
    this->obj = &obj;
}

void MoveAnim::SetObj(sf::Sprite &obj)
{
    this->obj = &obj;
}

void MoveAnim::SetObj(sf::RectangleShape &obj)
{
    this->obj = &obj;
}

void MoveAnim::SetObj(sf::CircleShape &obj)
{
    this->obj = &obj;
}

void MoveAnim::move(float x, float y)
{
    obj->move(x, y);
}

MoveAnim::MoveAnim()
{
}

MoveAnim::~MoveAnim()
{
}
