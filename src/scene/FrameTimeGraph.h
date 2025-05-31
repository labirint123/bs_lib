#pragma once
#include "GraphWidget.h"

class FrameTimeGraph : public GraphWidget
{
private:
    sf::Clock TimerMs;
    sf::Clock TimerSec;
    unsigned int Frames = 0;
    std::string FPSSTR;

public:
    FrameTimeGraph();
    void UpdateFrame();
};
