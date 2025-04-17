#include <SFML/Graphics.hpp>
#include "DebugInfoUi.h"
#include "Raleway.h"
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 600), "DebugInfoUi Test", sf::Style::Default, settings);


    sf::Font font;
    font.loadFromMemory(Raleway,Raleway_len);

    Parameter fpsPar{"Frame Time in ms", 0.f, sf::Color::Cyan};


    DebugInfoUi debugUi;
    debugUi.SetFont(font);
    debugUi.SetTimeWindow(1.f);
    debugUi.AddParameter(fpsPar);

    sf::Clock clock;
    float dt;
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
            if (ev.type == sf::Event::Closed)
                window.close();

        dt = clock.restart().asSeconds() * 1000;
        fpsPar.value = dt;
        

        debugUi.Update();

        window.clear(sf::Color(30, 30, 30));
        window.draw(debugUi);
        window.display();
    }

    return 0;
}
