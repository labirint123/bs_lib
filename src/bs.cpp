#include "bs.h"
#include "Animator.h"

#include <thread>

bool bs::IsProgrammEnd = 0;

bs::bs()
{
}

void bs::bsInit()
{
    l.module = "BS";

    Animator a;
    Animator::coreCount = std::thread::hardware_concurrency();
    l.Log("cores: " + std::to_string(a.coreCount));
    Animator::trc.setTimesPerSec(1000);
    for (size_t i = 0; i < a.coreCount; i++)
    {
        ThreadPoolThread *t = new ThreadPoolThread();        
        Animator::thread_pool.push_back(t);
    }
    for (size_t i = 0; i < a.coreCount; i++)
    {
        Animator::thread_pool.at(i)->index = i;
        Animator::thread_pool.at(i)->thread = std::thread(Animator::StartCicle, i);
    }
}

bs::~bs()
{
}
