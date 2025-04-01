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
    void Abort() { isAborted = 1; }

    void SetAnimationType(AnimationType type) { this->type = type; }
    void SetDeltaTime(sf::Time time) { this->DeltaTime = time; }
    void SetCiclic(bool isCiclic) { this->isCiclic = isCiclic; }
    sf::Time GetDeltaTime() { return this->DeltaTime; }
    bool IsStarted() { return isStarted; }
    bool IsFinished() { return this->isFinised; }
    bool IsAborted() { return this->isAborted; }
    bool IsCiclic() { return this->isCiclic; }
    float GetProgress() { return LastProgress; }
    AnimationType GetAnimationType() { return this->type; }
    sf::Time GetPassedTime() { return timePassed.getElapsedTime(); }

protected:
    AnimationType type;
    virtual void MakeAMove(float UpdatedProgress) = 0;
    virtual void ToDoAtStart() {}
    sf::Time DeltaTime;
    bool isFinised = 0;
    bool isAborted = 0;
    bool isStarted = 0;
    bool isCiclic = 0;
    sf::Clock timePassed;
    float LastProgress = 0;
    friend Animator;
};
