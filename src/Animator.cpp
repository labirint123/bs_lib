#include "Animator.h"
#include "Anim.h"
#include "bs.h"
#include "BsLogger.h"
#include <cmath>
unsigned int Animator::coreCount = 0;
std::vector<ThreadPoolThread *> Animator::thread_pool;
TickRateController Animator::trc;

void Animator::linear(Anim *anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double pprogress = progress / anim->time.asSeconds();
    if (anim->moveOffset.x * pprogress < 1 || anim->moveOffset.y * pprogress < 1)
        return;
    anim->move(anim->moveOffset.x * pprogress, anim->moveOffset.y * pprogress);
    anim->progress += progress;
}

double CalcEaseOutCubic(double x)
{
    return 1 - std::pow(1 - x, 3);
}
void Animator::easeOutCubic(Anim *anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = CalcEaseOutCubic(anim->progress);
    double actProgress = CalcEaseOutCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;
    if (anim->moveOffset.x * diffProgress < 1 || anim->moveOffset.y * diffProgress < 1)
        return;
    anim->move(anim->moveOffset.x * diffProgress, anim->moveOffset.y * diffProgress);
    anim->progress += progress;
}

double CaclcEaseInCubic(double x)
{
    return x * x * x;
}
void Animator::easeInCubic(Anim *anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = CaclcEaseInCubic(anim->progress);
    double actProgress = CaclcEaseInCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;
    if (anim->moveOffset.x * diffProgress < 1 || anim->moveOffset.y * diffProgress < 1)
        return;
    anim->move(anim->moveOffset.x * diffProgress, anim->moveOffset.y * diffProgress);
    anim->progress += progress;
}

double calcEaseInOutCubic(double x)
{
    return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
}
void Animator::easeInOutCubic(Anim *anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = calcEaseInOutCubic(anim->progress);
    double actProgress = calcEaseInOutCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;
    if (anim->moveOffset.x * diffProgress < 1 || anim->moveOffset.y * diffProgress < 1)
        return;
    anim->move(anim->moveOffset.x * diffProgress, anim->moveOffset.y * diffProgress);
    anim->progress += progress;
}

void Animator::StartCicle(const int ThreadIndex)
{
    BsLogger l;
    l.module = "AnimationThread(" + std::to_string(ThreadIndex) + ")";
    l.Log("started");
    std::vector<Anim *> *anims = &Animator::thread_pool.at(ThreadIndex)->animations; // иногда тут вылетает

    while (!bs::IsProgrammEnd)
    {
        for (size_t i = 0; i < anims->size(); i++)
        {
            if (anims->at(i)->timePassed.getElapsedTime().asSeconds() >= anims->at(i)->time.asSeconds())
            {
                anims->erase(anims->begin() + i);
                Animator::thread_pool.at(ThreadIndex)->TasksCount--;
                continue;
            }

            if (anims->at(i)->GetAnimationType() == Anim::AnimationType::linear)
                Animator::linear(anims->at(i));
            else if (anims->at(i)->GetAnimationType() == Anim::AnimationType::easeInOutCubic)
                Animator::easeInOutCubic(anims->at(i));
            else if (anims->at(i)->GetAnimationType() == Anim::AnimationType::easeInCubic)
                Animator::easeInCubic(anims->at(i));
            else if (anims->at(i)->GetAnimationType() == Anim::AnimationType::easeOutCubic)
                Animator::easeOutCubic(anims->at(i));
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
