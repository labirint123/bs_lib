#include "ViewAnim.h"

void ViewAnim::ToDoAtStart()
{
    PassedMove = {0, 0};
}

void ViewAnim::SetZoomOffset(float offset)
{
    this->ZoomOffset = offset;
}

void ViewAnim::SetRotationOffset(float offset)
{
    RotationOffset = offset;
}

void ViewAnim::SetMoveOffset(sf::Vector2i offset)
{
    MoveOffset = offset;
}
void ViewAnim::SetFinalRotation(float Rotation)
{
    RotationOffset = Rotation - view->getRotation();
}

void ViewAnim::SetFinalPosition(sf::Vector2i CenterPos)
{
    MoveOffset = {CenterPos.x - view->getCenter().x,
                  CenterPos.y - view->getCenter().y};
}

void ViewAnim::MakeAMove(float UpdatedProgress)
{
    float diffP = UpdatedProgress - this->LastProgress;

    sf::Vector2i totalMove = {MoveOffset.x * UpdatedProgress,
                              MoveOffset.y * UpdatedProgress};
    sf::Vector2i deltaMove = totalMove - PassedMove;

    float totalRotate = RotationOffset * UpdatedProgress;
    float prevRotate = RotationOffset * this->LastProgress;
    float deltaRotate = totalRotate - prevRotate;
    if (std::abs(deltaMove.x) >= 1 || std::abs(deltaMove.y) >= 1)
    {
        PassedMove += deltaMove;
        view->move(deltaMove.x, deltaMove.y);
    }
    view->rotate(deltaRotate);
    this->LastProgress = UpdatedProgress;
}
