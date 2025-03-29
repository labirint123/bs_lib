#pragma once
#include "bs.h"
#include <thread>
#include <vector>
#include "TickRateController.h"
#include "Animation.h"
#include <memory>

struct ThreadPoolThread;
class Anim;
class Animation;

class Animator
{
private:
    static TickRateController trc;
    static unsigned int coreCount;
    static std::vector<ThreadPoolThread *> thread_pool;

public:
    static void StartCicle(int ThreadIndex);
    Animator(/* args */);
    ~Animator();

    friend bs;
    friend Anim;
    friend Animation;
};

struct ThreadPoolThread
{
    std::thread thread;
    unsigned int TasksCount;
    int index;
    std::vector<Animation *> animations;

    ThreadPoolThread()
    {
    }
};