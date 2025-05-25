#include "DebugScene.h"

DebugScene::DebugScene()
{
    MemGr.Start();
    MemGr.SetView(DefaultView);

    FrameGr.SetView(DefaultView);
    FrameGr.setPosition({0, 110});

    pb.setText("PushButton :)");
    pb.SetView(DefaultView);

    add(MemGr);
    WidgetsGr.add(pb);
    WidgetsGr.add(pr);
    add(WidgetsGr);
    add(FrameGr);
    pb.setPosition({0, 0});
    pr.setPosition({0, pb.getSize().y + 10});

    pb.onClick.connect([this](bool down)
                       {
        if (pr.GetValue() >= pr.GetMaxValue() && down)   this->pr.SetValue(0);
        else if (down)   this->pr.SetValue(this->pr.GetValue() + 10); });
}

void DebugScene::Resize(sf::Vector2f NewSize)
{
    DefaultView.setSize(NewSize);
    DefaultView.setCenter({NewSize.x / 2, NewSize.y / 2});
    WidgetsGr.setPosition(GetAlignedPosition(NewSize, {0, 0},
                                             {WidgetsGr.getBounds().getSize().x, WidgetsGr.getBounds().getSize().y},
                                             WidgetsGr.getPosition(), Aligns::Center));
}

void DebugScene::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    MemGr.HandleEvent(event, window);
    pb.HandleEvent(event, window, WidgetsGr.getTransform());
    pr.HandleEvent(event, window);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
    {
        pb.SetEnabled(!pb.Enabled());
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
    {
        pb.SetVisibility(!pb.IsVisible());
        pr.SetVisibility(!pr.IsVisible());
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

void DebugScene::AfterDraw()
{
    FrameGr.UpdateFrame();
}