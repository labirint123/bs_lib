#include "Animation.h"
#include "Animator.h"


bool Animation::Start()
{
    if (this->LastProgress != 0)
        return 1;

    this->LastProgress = 0;
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
    Animator::thread_pool.at(min)->animations.push_back(this);
    return 0;
}