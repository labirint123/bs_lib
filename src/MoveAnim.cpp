#include "MoveAnim.h"

void MoveAnim::MakeAMove(float UpdatedProgress)
{
    float diffP = UpdatedProgress - this->LastProgress;
    if (std::abs(this->moveOffset.x * diffP) >= 1.f)
    {
        this->LastProgress = UpdatedProgress;
        this->move(this->moveOffset.x * diffP, 0);
    }
    if (std::abs(this->moveOffset.y * diffP) >= 1.f)
    {
        this->LastProgress = UpdatedProgress;
        this->move(this->moveOffset.y * diffP, 0);
    }
}

bool MoveAnim::IsFinished() const
{
    return false;
}

void MoveAnim::Abort()
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
