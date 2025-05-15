#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "RoundedRectangleShape.hpp"
#include "MemoryUsageGraph.h"
#include "GraphWidget.h"
#include "bs.h"

/*
Before optimizaton:

avg for 3 graphs = 0.05 - 0.06ms

After

avg for 3 graphs = 0.045

*/

int main(int argc, char *argv[])
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Hitbox Test",
        sf::Style::Default,
        settings);
    window.setVerticalSyncEnabled(0);

    bs core;
    core.bsInit(argc, argv);

    MemoryUsageGraph MemGr;
    MemGr.Start();

    GraphWidget FrameTimeGr;
    FrameTimeGr.SetLabel("frame time");
    FrameTimeGr.move({0, MemGr.getBounds().height + 10});
    sf::Clock FrameTimer;
    float FrameTimeVal = 0;
    FrameTimeGr.SetValue(FrameTimeVal);

    GraphWidget DeltaTimeOfGraphs;
    DeltaTimeOfGraphs.SetSize({600,300});
    DeltaTimeOfGraphs.SetLabel("avg for 3 graphs");
    DeltaTimeOfGraphs.move({0, (MemGr.getBounds().height + 10) * 2});
    sf::Clock deltaGraphTimer;
    float DeltaGraphVal = 0;
    DeltaTimeOfGraphs.SetValue(DeltaGraphVal);
    std::vector<float> All;
    bool IsDrawGraphs = 1;

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed)
            {
                switch (e.key.code)
                {
                case sf::Keyboard::F3:
                    IsDrawGraphs = !IsDrawGraphs;
                    break;

                default:
                    break;
                }
            }
        }
        FrameTimeVal = FrameTimer.restart().asSeconds() * 1000;
        FrameTimeGr.Update();
        window.clear(sf::Color::Black);

        deltaGraphTimer.restart();
        if (IsDrawGraphs)
        {
            window.draw(MemGr);
            window.draw(FrameTimeGr);
            window.draw(DeltaTimeOfGraphs);
        }

        DeltaGraphVal = deltaGraphTimer.getElapsedTime().asSeconds() * 1000;
        All.push_back(DeltaGraphVal);
        float sum = 0;
        for (size_t i = 0; i < All.size(); i++)
        {
            sum += All[i];
        }
        sum /= All.size();
        DeltaGraphVal  = sum;
        DeltaTimeOfGraphs.Update();
        window.display();
    }

    return 0;
}
