#include <SFML/Graphics.hpp>
#include "bs.h"
#include "Animator.h"
#include "Raleway.h"
#include <vector>
#include <iostream>
#include "MoveAnim.h"


int main()
{
    bs b;
    b.bsInit();

    sf::Font font;
    font.loadFromMemory(Raleway, Raleway_len);
    sf::Text txt;
    txt.setString("hi, its example of how good \nc++ really is :)");
    txt.setFont(font);

    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");

    std::vector<sf::RectangleShape *> rects;
    for (size_t i = 0; i < 4; i++)
    {
        rects.push_back(new sf::RectangleShape({80, 80}));
        rects.at(i)->setFillColor(sf::Color::White);
        rects.at(i)->setPosition(100, 100 * i + 100);
        rects.at(i)->setFillColor(sf::Color(200, 30, 10));
    }
    std::vector<MoveAnim *> anims;
    for (size_t i = 0; i < 4; i++)
    {
        anims.push_back(new MoveAnim);
        anims.at(i)->SetAnimationType((Animation::AnimationType)i);
        anims.at(i)->SetMoveOffset(sf::Vector2f(300, 0));
        anims.at(i)->SetObj(*rects.at(i));
        anims.at(i)->SetDeltaTime(sf::seconds(1));
    }
    for (size_t i = 0; i < 4; i++)
    {
        anims.at(i)->Start();
    }
    sf::Clock c;
    c.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                bs::IsProgrammEnd = 1;
            }
            else
            {
                if (event.type == sf::Event::KeyPressed)
                {
                }
            }
        }
        if (c.getElapsedTime().asSeconds() > 1.2)
        {
            for (size_t i = 0; i < 4; i++)
            {
                rects.at(i)->setPosition(100, 100 * i + 100);
                anims.at(i)->Start();
            }
            c.restart();
        }
        window.clear(sf::Color(20, 5, 5));

        for (size_t i = 0; i < 4; i++)
        {
            window.draw(*rects.at(i));
        }

        window.draw(txt);
        window.display();
    }

    return 0;
}