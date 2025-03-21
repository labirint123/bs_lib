#include <SFML/Graphics.hpp>
#include "bs.h"
#include "Anim.h"
#include "Animator.h"
int main()
{
    bs b;
    b.bsInit();

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setPosition(100, 100);
    shape.setFillColor(sf::Color(200, 30, 10));
    Anim a;
    a.SetObj(shape);
    a.SetMoveOffset(sf::Vector2f(200, 200));
    a.SetTime(sf::seconds(1));
    a.SetAnimationType(Anim::AnimationType::easeInOutCubic);
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
                    if (event.key.code == sf::Keyboard::E)
                    {
                        shape.setPosition(0, 0);

                        a.Start();
                    }
                }
            }
        }

        window.clear(sf::Color(20, 5, 5));
        window.draw(shape);
        window.display();
    }
    
    return 0;
}