#pragma once
#include "Log.h"
#include <vector>
#include <string>
#include "Raleway.h"
#include <SFML/Graphics.hpp>

class bs
{
private:
    static std::vector<std::string> args;
    static void init(int argc, char *argv[], unsigned int ThreadConunt);
public:
    static sf::Font* DefaultFont;
    static bool ArgsContains(std::string str);
    static std::vector<std::string> GetArgs();
    static bool IsProgrammEnd;
    static void bsInit(int argc, char *argv[]);
    static void bsInit(int argc, char *argv[], unsigned int ThreadConunt);
};
