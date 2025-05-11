#include "bs.h"
#include "Animator.h"
#include <thread>
#include <sstream>
#include <algorithm>
#include <iostream>

std::vector<std::string> bs::args = std::vector<std::string>();
bool bs::IsProgrammEnd = false;
sf::Font* bs::DefaultFont = nullptr;

void bs::init(int argc, char *argv[], unsigned int ThreadConunt)
{
    //  ARGS
    args.clear();
    for (int i = 1; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    // DEFAULT FONT
    DefaultFont = new sf::Font();
    DefaultFont->loadFromMemory(Raleway, Raleway_len);

    //  ANIMATOR
    Animator a;
    Animator::coreCount = ThreadConunt;
    Log("cores: " + std::to_string(Animator::coreCount));
    Animator::trc.setTimesPerSec(1000);

    for (unsigned i = 0; i < Animator::coreCount; ++i)
    {
        auto t = new ThreadPoolThread();
        Animator::thread_pool.push_back(t);
    }
    for (unsigned i = 0; i < Animator::coreCount; ++i)
    {
        Animator::thread_pool[i]->index = static_cast<int>(i);
        Animator::thread_pool[i]->thread = std::thread(Animator::StartCicle, i);
    }
}

bool bs::ArgsContains(std::string str)
{
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == str)
            return 1;
        Log(args[i]);
    }

    return 0;
}

std::vector<std::string> bs::GetArgs()
{
    return args;
}

void bs::bsInit(int argc, char *argv[])
{
    
    init(argc,argv,std::thread::hardware_concurrency());
}

void bs::bsInit(int argc, char *argv[], unsigned int ThreadConunt)
{
    init(argc,argv,ThreadConunt);
}
