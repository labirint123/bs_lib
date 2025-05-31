#include "Animation.h"
#include "Animator.h"

int Animation::Start()
{
    if (this->LastProgress != 0 || isStarted)
        return -1;
    ToDoAtStart();
    if (this->DeltaTime == sf::seconds(0))
    {
        this->MakeAMove(1);
        isFinised = 1;
        LastProgress = 0;
        return 0;
    }
    this->LastProgress = 0;
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
    this->timePassed.restart();
    Animator::thread_pool.at(min)->animations.push_back(this);
    isStarted = 1;
    return min;
}

bool Animation::Start(unsigned int ThreadId)
{
    if (this->LastProgress != 0 || isStarted || ThreadId > Animator::thread_pool.size() - 1)
        return true;
    ToDoAtStart();
    if (this->DeltaTime == sf::seconds(0))
    {
        this->MakeAMove(1);
        isFinised = 1;
        LastProgress = 0;
        return 0;
    }
    this->LastProgress = 0;
    this->timePassed.restart();

    Animator::thread_pool.at(ThreadId)->TasksCount++;
    Animator::thread_pool.at(ThreadId)->animations.push_back(this);
    isStarted = 1;

    return false;
}

Animation* Animation::StartClone()
{
    Animation* clone = this->Clone();
    clone->isAborted = 0;
    clone->isStarted = 0;
    clone->LastProgress = 0;
    this->Cloned.push_back(clone);
    int ret = clone->Start();
    for (size_t i = 0; i < Cloned.size(); i++)
    {
        if (Cloned[i] == nullptr)
        {
            Cloned.erase(Cloned.begin() + i);
            continue;
        }
        else if (Cloned[i]->IsFinished() || Cloned[i]->IsAborted())
        {
            delete Cloned[i];
            Cloned[i] = nullptr;
            Cloned.erase(Cloned.begin() + i);
        }
    }

    return clone;
}
