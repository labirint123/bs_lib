#pragma once
#include <string>

class BsLogger
{
private:
public:
    std::string module;
    void Log(std::string str);
    void Log(int str);
    void Log(unsigned int str);
    void Log(double str);
    void Log(float str);
    BsLogger(/* args */);
    ~BsLogger();
};