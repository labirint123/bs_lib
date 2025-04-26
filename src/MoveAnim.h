#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "UsesTransformable.h"

class MoveAnim : public Animation, public UsesTransformable
{
public:
    void MakeAMove(float UpdatedProgress) override;
    void SetMoveOffset(sf::Vector2f offset);

private:
    sf::Vector2f moveOffset;

protected:
    Animation *Clone() const override { return new MoveAnim(*this); }
};
