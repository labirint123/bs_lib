#include "BsLogger.h"
#include <iostream>
void BsLogger::Log(std::string str)
{
    std::cout << this->module << ": " <<  str << std::endl;
}

void BsLogger::Log(int str)
{
    this->Log(std::to_string(str));
}

void BsLogger::Log(unsigned int str)
{
    this->Log(std::to_string(str));
}

void BsLogger::Log(double str)
{
    this->Log(std::to_string(str));
}

void BsLogger::Log(float str)
{
    this->Log(std::to_string(str));
}

BsLogger::BsLogger()
{
}

BsLogger::~BsLogger()
{
}
