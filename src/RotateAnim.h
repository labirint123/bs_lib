#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "UsesTransformable.h"

class RotateAnim : public Animation, public UsesTransformable
{
public:
    void MakeAMove(float UpdatedProgress) override;
    void ToDoAtStart() override;
    void SetRotation(float offset);

private:
    Animation *Clone() const override { return new RotateAnim(*this); }
    float rotateDiff;
};
