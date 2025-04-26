#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "UsesTransformable.h"

class ScaleAnim : public Animation, public UsesTransformable
{
private:
    void MakeAMove(float UpdatedProgress) override;
    void ToDoAtStart() override;
    Animation *Clone() const override { return new ScaleAnim(*this); }

public:
    void SetScaleOffset(sf::Vector2f ScaleOffset);

private:
    sf::Vector2f ScaleOffset = {0, 0};
    sf::Vector2f StartScale = {0, 0};

    // SizeAnim();
    // ~SizeAnim();
};