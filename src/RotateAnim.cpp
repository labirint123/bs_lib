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
