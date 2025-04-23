#include <SFML/Graphics.hpp>
#include "GraphWidget.h"
#include "Raleway.h"
#include <cmath>
#include "RoundedRectangleShape.hpp"
#include "Utils.hpp"
#include "Log.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window({1600, 900}, "GraphWidget Test", sf::Style::Default, settings);

    sf::Font font;
    if (!font.loadFromMemory(Raleway, Raleway_len))
        return -1;

    float rectsizes = 100;
    float margin = 20;

    std::vector<Group> grps(13);
    for (size_t i = 0; i < grps.size(); i++)
    {
        auto *r = new RoundedRectangleShape();
        r->setSize({rectsizes, rectsizes});
        grps[i].add(r);

        grps[i].setPosition({(rectsizes + margin) * i, 0});

        auto *v = new RoundedRectangleShape();
        v->setSize({rectsizes / 3.f, rectsizes / 3.f});
        v->setFillColor(sf::Color::Red);

        grps[i].add(v);

        Align(*v, *r, (Aligns)i);
    }
    Group all;
    for (size_t i = 0; i < grps.size(); i++)
    {
        all.add(grps[i]);
    }
    Align(all, window, Center);

    float FrameTime = 0;
    GraphWidget graph;
    graph.SetFont(font);
    graph.SetGraphColor(sf::Color::Green);
    graph.SetLabel("frameTime in ms");
    graph.SetTimeWindow(5.f);
    graph.setPosition({10.f, 10.f});
    graph.SetValue(FrameTime);

    sf::Text fpsText("", font, 16);
    fpsText.setPosition(10.f, 320.f);
    fpsText.setFillColor(sf::Color::White);
    sf::Clock fpsClock;
    int fpsCounter = 0;
    sf::Clock FrameTimer;

    bool isdeb = 1;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
            else if (ev.type == sf::Event::KeyReleased)
            {
                if (ev.key.code == sf::Keyboard::F3)
                {
                    isdeb = !isdeb;
                    graph.ClearData();
                }
            }
        }

        if (fpsClock.getElapsedTime().asSeconds() >= 1.f)
        {
            fpsText.setString("FPS: " + std::to_string(fpsCounter));
            fpsCounter = 0;
            fpsClock.restart();
        }
        fpsCounter++;

        FrameTime = FrameTimer.restart().asSeconds() * 1000;

        window.clear({30, 30, 30});
        if (isdeb)
        {
            graph.Update();
            window.draw(graph);
        }
        window.draw(fpsText);
        window.draw(all);
        window.display();
    }
    return 0;
}