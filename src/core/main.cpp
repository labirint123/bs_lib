#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "RoundedRectangleShape.hpp"
#include "MemoryUsageGraph.h"
#include "GraphWidget.h"
#include "bs.h"
#include "PushButton.h"
#include "Scene.h"
#include "ProgressBar.h"

class DebugScene : public Scene
{
private:
    MemoryUsageGraph MemGr;
    PushButton pb;
    ProgressBar pr;
    bool IsEnabled = 1;
    sf::RectangleShape* r = new sf::RectangleShape();

public:
    DebugScene();
    void Resize(sf::Vector2f NewSize);
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
    {
        MemGr.HandleEvent(event, window);
        pb.HandleEvent(event, window);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
        {
            pb.SetEnabled(!pb.Enabled());
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
        {
            pb.SetVisibility(!pb.IsVisible());
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
        {
            pr.SetValue(pr.GetValue() + 1);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
        {
            pr.SetValue(pr.GetValue() - 1);
        }
    }
};

DebugScene::DebugScene()
{
    MemGr.Start();
    MemGr.SetView(DefaultView);

    pb.setText("PushButton :)");
    pb.SetView(DefaultView);

    add(MemGr);
    add(pb);
    add(pr);

    r->setSize(GetSize(pb.GetText()));
    r->setPosition(pb.GetText().getPosition() + pb.getPosition());
    r->setFillColor({0,0,0,100});
    // add(r);
}

void DebugScene::Resize(sf::Vector2f NewSize)
{
    DefaultView.setSize(NewSize);
    DefaultView.setCenter({NewSize.x / 2, NewSize.y / 2});
    pb.setPosition(GetAlignedPosition(NewSize, {0, 0}, pb.getSize(), pb.getPosition(), Aligns::Center));
    pr.setPosition({pb.getPosition().x, pb.getPosition().y + pb.getSize().y + 20});
    r->setSize(GetSize(pb.GetText()));
    r->setPosition(pb.GetText().getPosition() + pb.getPosition());
}

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

    DebugScene deb;
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
                view.setSize({window.getSize().x, window.getSize().y});
                view.setCenter({window.getSize().x / 2, window.getSize().y / 2});
                window.setView(view);
                deb.Resize({window.getSize().x, window.getSize().y});
            }
            deb.HandleEvent(e, window);
        }

        window.clear(sf::Color(20, 20, 20));
        window.draw(deb);
        window.display();
    }

    return 0;
}
