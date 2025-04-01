#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "UsesTransformable.h"

class MoveAnim : public Animation, public UsesTransformable
{
public:
    void MakeAMove(float UpdatedProgress) override;
    void ToDoAtStart() override;
    void SetMoveOffset(sf::Vector2f offset);

private:
    sf::Vector2f moveOffset;
    void move(float x, float y);

public:
    MoveAnim(/* args */);
    ~MoveAnim();
};
