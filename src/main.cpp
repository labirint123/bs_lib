#include <SFML/Graphics.hpp>
#include "DebugInfoUi.h"
#include "Raleway.h"      // здесь лежит const char Raleway[], int Raleway_len
#include <iostream>
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(800,600),
        "DebugInfoUi Test",
        sf::Style::Default,
        settings
    );

    sf::Font font;
    if (!font.loadFromMemory(Raleway, Raleway_len))
    {
        std::cerr << "Failed to load embedded font\n";
        return 1;
    }

    DebugInfoUi d;
    d.SetFont(font);

    d.SetPosition({10.f, 10.f});

    parameter p("test", 0.f, sf::Color::White);
    d.AddParameter(p);

    d.Update();

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::TextEntered && e.text.unicode < 128)
            {
                char c = static_cast<char>(e.text.unicode);
                if (std::isprint(c))
                {
                    p.value += 1.f;
                    d.Update();
                }
            }
        }

        window.clear(sf::Color(20,5,5));
        window.draw(d);
        window.display();
    }

    return 0;
}
