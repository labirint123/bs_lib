#include <SFML/Graphics.hpp>
#include "ViewAnim.h"
#include "GraphWidget.h"
#include "Raleway.h"
#include <cmath>
#include "RoundedRectangleShape.hpp"
#include "Utils.hpp"
#include "Log.h"
#include "bs.h"
#include "OsStates.h"

int main()
{
    bs eng;
    eng.bsInit();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
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
        r->setCornerRadius(rectsizes / 4);
        grps[i].setPosition({(rectsizes + margin) * i, 0});

        auto *v = new RoundedRectangleShape();
        v->setSize({rectsizes / 3.f, rectsizes / 3.f});
        v->setFillColor(sf::Color::Red);
        v->setCornerRadius(rectsizes / 3 / 4);
        grps[i].add(v);

        Align(*v, *r, (Aligns)i);
    }
    Group all;
    for (size_t i = 0; i < grps.size(); i++)
    {
        all.add(grps[i]);
    }
    Align(all, window, Center);

    sf::View vi(window.getDefaultView());
    ViewAnim va;
    va.SetObj(vi);
    va.SetAnimationType(Animation::AnimationType::easeInOutCubic);
    va.SetDeltaTime(sf::seconds(1));
    // va.SetMoveOffset({50, 0});
    va.SetRotationOffset(50);

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
    while (!eng.IsProgrammEnd)
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                eng.IsProgrammEnd = 1;
                window.close();
            }
            else if (ev.type == sf::Event::KeyReleased)
            {
                if (ev.key.code == sf::Keyboard::F)
                {
                    va.StartClone();
                }
                if (ev.key.code == sf::Keyboard::Q)
                {
                    eng.IsProgrammEnd = 1;
                    window.close();
                }
                if (ev.key.code == sf::Keyboard::M)
                {
                    int *a = new int[999999];
                    for (size_t i = 0; i < 999999; ++i)
                    {
                        a[i] = i; 
                    }

                    Log("int* a = new int[999999];");
                }
                if (ev.key.code == sf::Keyboard::F3)
                {
                    isdeb = !isdeb;
                    graph.ClearData();
                }
            }
        }
        window.setView(vi);
        if (fpsClock.getElapsedTime().asSeconds() >= 1.f)
        {
            Log(OsStates::GetProcessMemoryUsage() / (1000.0 * 1000.0));
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