#include "Animator.h"
#include "Anim.h"
#include "bs.h"
#include "BsLogger.h"
#include <cmath>
#include <iostream>
unsigned int Animator::coreCount = 0;
std::vector<ThreadPoolThread *> Animator::thread_pool;
TickRateController Animator::trc;

void Animator::linear(Anim* anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double pprogress = progress / anim->time.asSeconds();

    float dx = anim->moveOffset.x * pprogress;
    float dy = anim->moveOffset.y * pprogress;

    if (std::abs(dx) < 1 && std::abs(dy) < 1)
        return;

    if (std::abs(dx) >= 1)
        anim->move(dx, 0);
    if (std::abs(dy) >= 1)
        anim->move(0, dy);

    anim->progress += progress;
}

double CalcEaseOutCubic(double x)
{
    return 1 - std::pow(1 - x, 3);
}

void Animator::easeOutCubic(Anim* anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = CalcEaseOutCubic(anim->progress);
    double actProgress = CalcEaseOutCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;

    float dx = anim->moveOffset.x * diffProgress;
    float dy = anim->moveOffset.y * diffProgress;

    if (std::abs(dx) < 1 && std::abs(dy) < 1)
        return;

    if (std::abs(dx) >= 1)
        anim->move(dx, 0);
    if (std::abs(dy) >= 1)
        anim->move(0, dy);

    anim->progress += progress;
}

double CaclcEaseInCubic(double x)
{
    return x * x * x;
}

void Animator::easeInCubic(Anim* anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = CaclcEaseInCubic(anim->progress);
    double actProgress = CaclcEaseInCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;

    float dx = anim->moveOffset.x * diffProgress;
    float dy = anim->moveOffset.y * diffProgress;

    if (std::abs(dx) < 1 && std::abs(dy) < 1)
        return;

    if (std::abs(dx) >= 1)
        anim->move(dx, 0);
    if (std::abs(dy) >= 1)
        anim->move(0, dy);

    anim->progress += progress;
}

double calcEaseInOutCubic(double x)
{
    return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
}

void Animator::easeInOutCubic(Anim* anim)
{
    double progress = anim->timePassed.getElapsedTime().asSeconds() - anim->progress;
    double prevProgress = calcEaseInOutCubic(anim->progress);
    double actProgress = calcEaseInOutCubic(anim->progress + progress);
    double diffProgress = actProgress - prevProgress;

    float dx = anim->moveOffset.x * diffProgress;
    float dy = anim->moveOffset.y * diffProgress;

    if (std::abs(dx) < 1 && std::abs(dy) < 1)
        return;

    if (std::abs(dx) >= 1)
        anim->move(dx, 0);
    if (std::abs(dy) >= 1)
        anim->move(0, dy);

    anim->progress += progress;
}

void Animator::StartCicle(const int ThreadIndex)
{
    BsLogger l;
    l.module = "AnimationThread(" + std::to_string(ThreadIndex) + ")";
    l.Log("started");
    std::vector<Anim*> *anims = &Animator::thread_pool.at(ThreadIndex)->animations;

    while (!bs::IsProgrammEnd)
    {
        for (size_t i = 0; i < anims->size(); i++)
        {
            if (anims->at(i)->timePassed.getElapsedTime().asSeconds() >= anims->at(i)->time.asSeconds())
            {
                anims->at(i)->isFinised = 1;
                anims->at(i)->progress = 0;
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
