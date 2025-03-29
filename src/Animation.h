#pragma once
#include <SFML/System.hpp>

class Animator;
class Animation
{
public:
    enum AnimationType
    {
        linear,
        easeOutCubic,
        easeInCubic,
        easeInOutCubic
    };

    virtual ~Animation() = default;

    bool Start();
    virtual bool IsFinished() const = 0;
    virtual void Abort() = 0;

    void SetAnimationType(AnimationType type) { this->type = type; }
    AnimationType GetAnimationType() { return this->type; }
    void SetDeltaTime(sf::Time time) { this->DeltaTime = time; }
    sf::Time GetDeltaTime() { return this->DeltaTime; }

protected:
    AnimationType type;
    virtual void MakeAMove(float UpdatedProgress) = 0;
    sf::Time DeltaTime;
    bool isFinised = 0;
    sf::Clock timePassed;
    float LastProgress = 0;
    friend Animator;
};
