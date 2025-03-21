#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.h"


class Animator;
class Anim
{
public:
    enum class AnimationType{linear,
        easeOutCubic,easeInCubic,easeInOutCubic};
private:
    struct AnimationObjs
    {
        sf::Text* Text;
        sf::Sprite* Sprite;
        sf::Shape* Shape;        
    };
    enum class CurrentObj{Text,Sprite,Shape};
    CurrentObj curobj;
    AnimationObjs Objs;
    bool isFinised = 0;
    AnimationType type;
    sf::Time time;
    sf::Clock timePassed;
    sf::Vector2f moveOffset;
    double progress;
    void move(float x, float y);
    // bool isStarted();
public:
    void SetObj(sf::Text &obj);
    void SetObj(sf::Sprite &obj);
    void SetObj(sf::RectangleShape &obj);
    void SetObj(sf::CircleShape &obj);
    void SetAnimationType(AnimationType type){this->type = type;}
    AnimationType GetAnimationType(){return this->type;}
    void SetTime(sf::Time time){this->time = time;}
    sf::Time GetTime(){return this->time;}
    void SetMoveOffset(sf::Vector2f moveOffset){this->moveOffset = moveOffset;}
    sf::Vector2f GetMoveOffset(){return this->moveOffset;}



    void Start();
    bool IsFinished(){return this->isFinised;}
    

    Anim();
    ~Anim();

    friend Animator;
};
