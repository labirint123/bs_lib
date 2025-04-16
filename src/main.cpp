#include <SFML/Graphics.hpp>
#include "bs.h"
#include "Animator.h"
#include "Raleway.h"
#include <vector>
#include <iostream>
#include "MoveAnim.h"
#include "ColorAnim.h"
#include "ScaleAnim.h"
#include "SizeAnim.h"
#include "RotateAnim.h"
#include "Group.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    bs b;
    b.bsInit();

    sf::Font font;
    font.loadFromMemory(Raleway, Raleway_len);
    sf::Text txt;
    txt.setString("font check");
    txt.setFont(font);

    std::vector<Group *> rects;
    for (size_t i = 0; i < 4; ++i)
    {
        rects.push_back(new Group());
        sf::RectangleShape *r = new sf::RectangleShape({80, 80});
        sf::Text *t = new sf::Text;
        t->setFont(font);
        t->setString("obj " + std::to_string(i));
        t->setFillColor(sf::Color::Black);
        r->setFillColor(sf::Color::White);

        sf::FloatRect bounds = r->getLocalBounds();
        rects[i]->SetOrigin({bounds.width / 2.f, bounds.height / 2.f});

        rects[i]->SetPosition({100, 100 * i + 100});
        rects[i]->add(*r);
        rects[i]->add(*t);

    }

    std::vector<MoveAnim *> moveanims;
    for (size_t i = 0; i < 4; i++)
    {
        moveanims.push_back(new MoveAnim);
        moveanims.at(i)->SetAnimationType((Animation::AnimationType)i);
        moveanims.at(i)->SetMoveOffset(sf::Vector2f(300, 0));
        moveanims.at(i)->SetObj(rects.at(i));
        moveanims.at(i)->SetDeltaTime(sf::seconds(1));
    }

    std::vector<RotateAnim *> rotateanims;
    for (size_t i = 0; i < 4; i++)
    {
        rotateanims.push_back(new RotateAnim);
        rotateanims.at(i)->SetAnimationType((Animation::AnimationType)i);

        rotateanims.at(i)->SetObj(rects.at(i));
        rotateanims.at(i)->SetRotation(180);
        rotateanims.at(i)->SetDeltaTime(sf::seconds(1));
    }

        for (size_t i = 0; i < 4; i++)
    {
        moveanims.at(i)->Start();
        rotateanims.at(i)->Start();
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
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode < 128)
                    {
                        char entered = static_cast<char>(event.text.unicode);

                        if (std::isprint(entered))
                        {
                            Log(entered);
                        }
                    }
                }
            }
        }
        if (c.getElapsedTime().asSeconds() > 2)
        {
            for (size_t i = 0; i < 4; i++)
            {
                rects.at(i)->SetPosition({100, 100 * i + 100});               
                rects.at(i)->SetScale({1, 1});                
                rotateanims.at(i)->Start();
                moveanims.at(i)->Start();
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
