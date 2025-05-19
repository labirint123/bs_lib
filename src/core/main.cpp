#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "RoundedRectangleShape.hpp"
#include "MemoryUsageGraph.h"
#include "GraphWidget.h"
#include "bs.h"
#include "PushButton.h"

/*
widget

сетаешь вьюв, на каждом кадре передаёшь ивент (и к сожалению окно)

наследник хэндлит и эмитит сигналы
ну типа фсё

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

    sf::View view;
    window.setView(view);

    MemoryUsageGraph MemGr;
    MemGr.Start();
    MemGr.SetView(view);

    PushButton pb;
    pb.setText("hello :)");
    pb.SetView(view);
    Align(pb, window, Aligns::Center);

    bool isDefRealizationNedded = 1;

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
                case sf::Keyboard::D:
                    pb.setDefaultSignalBehavior(isDefRealizationNedded);
                    isDefRealizationNedded = !isDefRealizationNedded;
                default:
                    break;
                }
            }
            else if (e.type == sf::Event::Resized)
            {
                view.setSize({window.getSize().x, window.getSize().y});
                view.setCenter({window.getSize().x / 2, window.getSize().y / 2});
                window.setView(view);
            }
            MemGr.HandleEvent(e, window);
            pb.HandleEvent(e, window);
        }

        window.clear();

        window.draw(MemGr);
        window.draw(pb);
        window.display();
    }

    return 0;
}
