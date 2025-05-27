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
    WidgetsGr.add(pr);
    WidgetsGr.add(pb);
    WidgetsGr.add(dd);
    add(WidgetsGr);
    add(FrameGr);
    pb.setPosition({0, 0});
    pr.setPosition({0, pb.getSize().y + 10});

    dd.setPosition({0, pr.getPosition().y + pr.getSize().y + 10});
    dd.SetPlaceHolderString("PlaceHolder");
    dd.SetView(DefaultView);


    pb.onClick.connect([this](bool down)
    {
        if (down)
        {
            if (pr.GetValue() >= pr.GetMaxValue())
                pr.SetValue(0);
            else
                pr.SetValue(pr.GetValue() + 10);

            std::string label = "item " + std::to_string(dd.items_count());

            Item it(label);


            dd.GetItemSignal(dd.AddItem(label)).connect([label](bool selected)
            {
                Log("===========");
                Log(label);
                if (selected) Log("selected");
                else Log("UNselected");
            });
        }
    });
}

void DebugScene::Resize(sf::Vector2f NewSize)
{
    DefaultView.setSize(NewSize);
    DefaultView.setCenter({NewSize.x / 2, NewSize.y / 2});
    sf::Vector2i pos(GetAlignedPosition(NewSize, {0, 0},
                                        {WidgetsGr.getBounds().getSize().x, WidgetsGr.getBounds().getSize().y},
                                        WidgetsGr.getPosition(), Aligns::Center));
    WidgetsGr.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
}

void DebugScene::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    MemGr.HandleEvent(event, window);
    pb.HandleEvent(event, window, &WidgetsGr.getTransform());
    pr.HandleEvent(event, window);
    dd.HandleEvent(event, window, &WidgetsGr.getTransform());

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
