#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "RoundedRectangleShape.hpp"
#include "MemoryUsageGraph.h"
#include "GraphWidget.h"
#include "bs.h"
#include "PushButton.h"
#include "Scene.h"
#include "ProgressBar.h"
#include "Group.h"
#include "FrameTimeGraph.h"
#include "DropDown.h"

class DebugScene : public Scene
{
private:
    MemoryUsageGraph MemGr;
    FrameTimeGraph FrameGr;
    PushButton pb;
    ProgressBar pr;
    DropDown dd;
    bool IsEnabled = 1;
    Group WidgetsGr;
    std::vector<Widget> WidgetsVec; 
public:
    DebugScene();
    void Resize(sf::Vector2f NewSize);
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void AfterDraw();
};
