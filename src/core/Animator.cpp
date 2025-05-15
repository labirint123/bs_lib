#include "Animator.h"
#include "bs.h"
#include "Log.h"
#include <cmath>
#include <iostream>
unsigned int Animator::coreCount = 0;
std::vector<ThreadPoolThread *> Animator::thread_pool;
TickRateController Animator::trc;

double CalcEaseOutCubic(double x)
{
    return 1 - std::pow(1 - x, 3);
}

double CaclcEaseInCubic(double x)
{
    return x * x * x;
}

double calcEaseInOutCubic(double x)
{
    return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
}

void Animator::StartCicle(const int ThreadIndex)
{
    Log("AnimationThread(" + std::to_string(ThreadIndex) + ")" + "started");
    std::vector<Animation *> *anims = &Animator::thread_pool.at(ThreadIndex)->animations;

    while (!bs::IsProgrammEnd)
    {
        for (size_t i = 0; i < anims->size(); i++)
        {
            if (anims->at(i) == nullptr){
                anims->erase(anims->begin() + i);
                continue;
            }
            if (anims->at(i)->timePassed.getElapsedTime().asSeconds() >= anims->at(i)->DeltaTime.asSeconds())
            {
                anims->at(i)->MakeAMove(1);

                if (anims->at(i)->isCiclic)
                {
                    anims->at(i)->LastProgress = 0;
                    anims->at(i)->timePassed.restart();
                    anims->at(i)->ToDoAtStart();
                    continue;
                }
                anims->at(i)->LastProgress = 0;
                anims->at(i)->isFinised = 1;
                anims->at(i)->isStarted = 0;
               

                anims->erase(anims->begin() + i);
                Animator::thread_pool.at(ThreadIndex)->TasksCount--;
                continue;
            }
            if (anims->at(i)->isAborted)
            {
                anims->at(i)->isFinised = 1;
                anims->at(i)->LastProgress = 0;
                anims->at(i)->isStarted = 0;
                anims->erase(anims->begin() + i);
                Animator::thread_pool.at(ThreadIndex)->TasksCount--;
                continue;
            }

            if (anims->at(i)->GetAnimationType() == Animation::AnimationType::linear)
                anims->at(i)->MakeAMove(anims->at(i)->timePassed.getElapsedTime().asSeconds() / anims->at(i)->DeltaTime.asSeconds());

            else if (anims->at(i)->GetAnimationType() == Animation::AnimationType::easeInOutCubic)
                anims->at(i)->MakeAMove(calcEaseInOutCubic(anims->at(i)->timePassed.getElapsedTime().asSeconds() / anims->at(i)->DeltaTime.asSeconds()));

            else if (anims->at(i)->GetAnimationType() == Animation::AnimationType::easeInCubic)
                anims->at(i)->MakeAMove(CaclcEaseInCubic(anims->at(i)->timePassed.getElapsedTime().asSeconds() / anims->at(i)->DeltaTime.asSeconds()));

            else if (anims->at(i)->GetAnimationType() == Animation::AnimationType::easeOutCubic)
                anims->at(i)->MakeAMove(CalcEaseOutCubic(anims->at(i)->timePassed.getElapsedTime().asSeconds() / anims->at(i)->DeltaTime.asSeconds()));
        }

        trc.ControlTicks();
    }
}

Animator::Animator()
{
}

Animator::~Animator()
{
}
