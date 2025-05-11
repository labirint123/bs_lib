#pragma once
#include "Log.h"
#include <vector>
#include <string>

class bs
{
private:
    static std::vector<std::string> args;

public:
    static bool ArgsContains(std::string str);
    static std::vector<std::string> GetArgs();
    static bool IsProgrammEnd;
    static void bsInit(int argc, char *argv[]);
    static void bsInit(int argc, char *argv[], unsigned int ThreadConunt);
};
