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
    font.loadFromMemory(C__sfml_engine_res_Raleway_ttf, C__sfml_engine_res_Raleway_ttf_len);
    sf::Text txt;
    txt.setString("hi, its example of how good \nc++ really is :)");
    txt.setFont(font);


    std::vector<sf::RectangleShape*> rects;
    for (size_t i = 0; i < 4; ++i)
    {
        rects.push_back(new sf::RectangleShape({ 80, 80 }));
        rects.back()->setFillColor(sf::Color::White);

        sf::FloatRect bounds = rects.back()->getLocalBounds();
        rects.back()->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

        rects.back()->setPosition(100, 100 * i + 100);
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

    std::vector<RotateAnim *> sizeanims;
    for (size_t i = 0; i < 4; i++)
    {
        sizeanims.push_back(new RotateAnim);
        sizeanims.at(i)->SetAnimationType((Animation::AnimationType)i);

        sizeanims.at(i)->SetObj(*rects.at(i));
        sizeanims.at(i)->SetRotation(180);

        // sizeanims.at(i)->SetCiclic(1);
        sizeanims.at(i)->SetDeltaTime(sf::seconds(1));
    }

    std::vector<ColorAnim *> colanims;
    for (size_t i = 0; i < 4; i++)
    {
        colanims.push_back(new ColorAnim);
        colanims.at(i)->SetAnimationType((Animation::AnimationType)i);

        colanims.at(i)->SetObj(*rects.at(i));
        colanims.at(i)->SetTarget(ColorAnim::Target::Fill);
        colanims.at(i)->SetColor(sf::Color::Red);

        colanims.at(i)->SetDeltaTime(sf::seconds(1));
    }

    for (size_t i = 0; i < 4; i++)
    {
        anims.at(i)->Start();
        sizeanims.at(i)->Start();
        colanims.at(i)->Start();
    }

    Group g;

    sf::RectangleShape t;
    t.setFillColor(sf::Color(10, 10, 10));
    t.setSize({100, 100});
    g.add(t);
    sf::Text tx;
    tx.setFont(font);
    tx.setString("hi");
    g.add(tx);
    g.SetRotation(30);
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
            g.SetPosition({g.GetPosition().x + 10, g.GetPosition().y + 10});
            for (size_t i = 0; i < 4; i++)
            {
                rects.at(i)->setPosition(100, 100 * i + 100);
                rects.at(i)->setSize({80, 80});
                rects.at(i)->setScale({1, 1});
                rects.at(i)->setFillColor(sf::Color::White);
                // std::cout << std::to_string(rects.at(i)->getPosition().x) << std::endl;
                sizeanims.at(i)->Start();
                anims.at(i)->Start();
                colanims.at(i)->Start();
            }
            c.restart();
        }
        window.clear(sf::Color(20, 5, 5));

        for (size_t i = 0; i < 4; i++)
        {
            window.draw(*rects.at(i));
        }
        window.draw(g);
        window.draw(txt);
        window.display();
    }

    return 0;
}