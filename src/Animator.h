#pragma once
#include "bs.h"
#include <thread>
#include <vector>
#include "TickRateController.h"
#include "Anim.h"
#include <memory>

struct ThreadPoolThread;
class Anim;


class Animator
{
private:
    static TickRateController trc;
    static unsigned int coreCount;
    static std::vector<ThreadPoolThread *> thread_pool;

    static void linear(Anim* anim);
    static void easeOutCubic(Anim* anim);
    static void easeInCubic(Anim* anim);
    static void easeInOutCubic(Anim* anim);

public:
    static void StartCicle(int ThreadIndex);
    Animator(/* args */);
    ~Animator();

    friend bs;
    friend Anim;
};

struct ThreadPoolThread
{
    std::thread thread;
    unsigned int TasksCount;
    int index;
    std::vector<Anim*> animations;
    
    ThreadPoolThread()
    {
        
    }
};