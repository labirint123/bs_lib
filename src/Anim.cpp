#include "Anim.h"
#include <iostream>
void Anim::move(float x, float y)
{
    if (this->curobj == CurrentObj::Shape)
        Objs.Shape->move(x, y);
    else if (this->curobj == CurrentObj::Sprite)
        Objs.Sprite->move(x, y);
    else if (this->curobj == CurrentObj::Text)
        Objs.Sprite->move(x, y);
}

void Anim::SetObj(sf::Text &obj)
{
    this->Objs.Text = &obj;
    this->curobj = CurrentObj::Text;
}

void Anim::SetObj(sf::Sprite &obj)
{
    this->Objs.Sprite = &obj;
    this->curobj = CurrentObj::Sprite;
}

void Anim::SetObj(sf::RectangleShape &obj)
{
    this->Objs.Shape = &obj;
    this->curobj = CurrentObj::Shape;
}

void Anim::SetObj(sf::CircleShape &obj)
{
    this->Objs.Shape = &obj;
    this->curobj = CurrentObj::Shape;
}

void Anim::Start()
{
    this->progress = 0;
    this->timePassed.restart();
    int min = 0;
    unsigned int minTasks = Animator::thread_pool.at(0)->TasksCount;

    for (size_t i = 1; i < Animator::coreCount; ++i)
    {
        unsigned int current = Animator::thread_pool.at(i)->TasksCount;
        if (current < minTasks)
        {
            minTasks = current;
            min = static_cast<int>(i);
        }
    }    
    Animator::thread_pool.at(min)->TasksCount++;
    Animator::thread_pool.at(min)->animations.push_back(new Anim(*this));
}

Anim::Anim()
{
}

Anim::~Anim()
{
}
