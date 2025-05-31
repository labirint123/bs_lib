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
    PushButton ValUpPb;
    PushButton ValDownPb;
    ProgressBar pr;
    DropDown dd;
    bool IsEnabled = 1;
    Group WidgetsGr;
    std::vector<Widget> WidgetsVec;
    Animation::AnimationType animType = Animation::easeInOutCubic;
    std::vector<RoundedRectangleShape*> shapes;
    std::vector<MoveAnim*> anims;
    sf::Clock AnimsClock;
    sf::Time AnimsTime = sf::seconds(1);
    sf::Time AnimsDeltaTime = sf::seconds((0.1));
    Group shapesGr;
    unsigned int ShapesCount = 15;
    float AnimsY = 500;
    unsigned int DoneCount = 0;
public:
    DebugScene();
    void Resize(sf::Vector2f NewSize);
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void StartAnims();
    void AfterDraw();
};
