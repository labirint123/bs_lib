#include <SFML/Graphics.hpp>
#include "GraphWidget.h"
#include "Raleway.h"
#include "GraphWidget.h"
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 600), "DebugInfoUi Test", sf::Style::Default, settings);

    sf::Font font;
    font.loadFromMemory(Raleway, Raleway_len);

    GraphWidget debugUi;
    debugUi.SetGraphColor(sf::Color::White);
    debugUi.SetLabel("Frame Time in ms");
    debugUi.SetFont(font);
    debugUi.SetTimeWindow(10);
    debugUi.SetPosition({10,10});
    sf::Clock clock;
    float dt;
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
            if (ev.type == sf::Event::Closed)
                window.close();

        debugUi.Update(clock.restart().asSeconds() * 1000.f);

        window.clear(sf::Color(30, 30, 30));
        window.draw(debugUi);
        window.display();
    }

    return 0;
}
