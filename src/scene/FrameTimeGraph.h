#pragma once
#include "GraphWidget.h"

class FrameTimeGraph : public GraphWidget
{
private:
    sf::Clock timer;
public:
    FrameTimeGraph();
    void UpdateFrame();
};
