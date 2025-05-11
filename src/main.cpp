#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"

class GameScene : public Scene
{
private:
    sf::RectangleShape rect;

public:
    GameScene()
    {
        rect.setFillColor(sf::Color::Green);
        add(rect);
    }

    void Resize(sf::Vector2f newSize) override
    {
        rect.setSize(newSize * 0.5f);
        rect.setPosition(newSize * 0.25f);
        DefaultView.setSize(newSize);
        DefaultView.setCenter(newSize.x / 2, newSize.y / 2);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scene Example");
    GameScene scene;
    scene.Resize(sf::Vector2f(window.getSize()));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
                scene.Resize(sf::Vector2f(event.size.width, event.size.height));
        }

        window.clear(sf::Color::Black);
        window.draw(scene);
        window.display();
    }

    return 0;
}
