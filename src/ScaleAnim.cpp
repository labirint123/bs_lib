#include "ScaleAnim.h"

void ScaleAnim::MakeAMove(float UpdatedProgress)
{
    sf::Vector2f newScale;
    newScale = StartScale + ScaleOffset * UpdatedProgress;
    obj->setScale(newScale);
    this->LastProgress = UpdatedProgress;
}

void ScaleAnim::ToDoAtStart()
{
    StartScale = obj->getScale();
}


void ScaleAnim::SetScaleOffset(sf::Vector2f ScaleOffset)
{
    this->ScaleOffset.x = ScaleOffset.x - 1;
    this->ScaleOffset.y = ScaleOffset.y - 1;
}