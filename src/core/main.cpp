#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "RoundedRectangleShape.hpp"
#include "MemoryUsageGraph.h"
#include "GraphWidget.h"
#include "bs.h"
#include "PushButton.h"
#include "Scene.h"
#include "ProgressBar.h"
#include "DebugScene.h"

int main(int argc, char* argv[])
{
    bs core;
    core.bsInit(argc, argv);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Example",
        core.ArgsContains("--FixedSize")
            ? (sf::Style::Titlebar | sf::Style::Close)
            : (sf::Style::Default),
        settings);
    window.setVerticalSyncEnabled(1);
    DebugScene deb;
    deb.Resize(sf::Vector2f(window.getSize().x, window.getSize().y));
    while (window.isOpen() || !bs::IsProgrammEnd)
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
                bs::IsProgrammEnd = 1;
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                switch (e.key.code)
                {
                case sf::Keyboard::Q:
                    window.close();
                    bs::IsProgrammEnd = 1;
                    break;

                default:
                    break;
                }
            }
            else if (e.type == sf::Event::Resized)
            {
                deb.Resize(sf::Vector2f(window.getSize().x, window.getSize().y));
            }
            deb.HandleEvent(e, window);
        }

        window.clear(sf::Color(20, 20, 20));
        window.draw(deb);
        deb.AfterDraw();
        window.display();
    }

    return 0;
}
