#pragma once
#include "Animation.h"
#include "UsesTransformable.h"
#include <SFML/Graphics.hpp>

class ViewAnim : public Animation
{
private:
    float ZoomOffset = 0;
    float RotationOffset = 0;
    sf::Vector2i PassedMove = {0, 0};
    sf::Vector2i MoveOffset = {0, 0};
    sf::View *view;
    void ToDoAtStart() override;
    Animation *Clone() const override { return new ViewAnim(*this); }
public:
    void SetZoomOffset(float offset);
    void SetRotationOffset(float offset);
    void SetMoveOffset(sf::Vector2i offset);

    void SetFinalRotation(float Rotation);
    void SetFinalPosition(sf::Vector2i CenterPos);

    void SetObj(sf::View &view) { this->view = &view; }

    void MakeAMove(float UpdatedProgress) override;
};
