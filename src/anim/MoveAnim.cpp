#include "MoveAnim.h"
#include "Log.h"

void MoveAnim::MakeAMove(float UpdatedProgress)
{
    float diffP = UpdatedProgress - this->LastProgress;

    sf::Vector2f totalMove = moveOffset * UpdatedProgress;
    sf::Vector2f prevMove  = moveOffset * this->LastProgress;
    sf::Vector2f delta     = totalMove - prevMove;

    this->LastProgress = UpdatedProgress;

    if (std::abs(delta.x) >= 0.001f || std::abs(delta.y) >= 0.001f || UpdatedProgress == 1)
    {
        Move({delta.x, delta.y});
        this->LastProgress = UpdatedProgress;
    }
}

void MoveAnim::SetMoveOffset(sf::Vector2f offset)
{
    this->moveOffset = offset;
}
