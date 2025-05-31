#include "DebugScene.h"

DebugScene::DebugScene()
{
    MemGr.Start();
    MemGr.SetView(DefaultView);

    FrameGr.SetView(DefaultView);
    FrameGr.setPosition({0, 110});

    ValUpPb.setText("Value UP");
    ValUpPb.SetView(DefaultView);
    ValUpPb.setSize({150, 35});

    ValDownPb.setText("Value Down");
    ValDownPb.SetView(DefaultView);
    ValDownPb.setSize({150, 35});

    add(MemGr);
    WidgetsGr.add(pr);
    WidgetsGr.add(ValUpPb);
    WidgetsGr.add(ValDownPb);
    WidgetsGr.add(dd);
    add(WidgetsGr);
    add(FrameGr);

    ValUpPb.setPosition({0, 0});

    ValDownPb.setPosition({0, ValUpPb.getSize().y + 10});

    pr.setPosition({0, ValDownPb.getBounds().height + ValDownPb.getBounds().top + 10});

    dd.setPosition({0, pr.getPosition().y + pr.getSize().y + 10});
    dd.SetPlaceHolderString("PlaceHolder");
    dd.SetView(DefaultView);

    dd.GetItemSignal(dd.AddItem("InCubic")).connect([this](bool selected)
    {
        animType = Animation::easeInCubic;
    });
    dd.GetItemSignal(dd.AddItem("InOutCubic")).connect([this](bool selected)
    {
        animType = Animation::easeInOutCubic;
    });
    dd.GetItemSignal(dd.AddItem("OutCubic")).connect([this](bool selected)
    {
        animType = Animation::easeOutCubic;
    });
    dd.GetItemSignal(dd.AddItem("linear")).connect([this](bool selected)
    {
        animType = Animation::linear;
    });
    dd.SelectItem(2);


    ValUpPb.onClick.connect([this](bool down)
    {
        if (down)
        {
            if (pr.GetValue() >= pr.GetMaxValue())
                pr.SetValue(0);
            else
            {
                pr.SetValue(pr.GetValue() + 10);
            }
            AnimsTime += sf::seconds(0.5);
            for (auto it : shapes)
            {
                it->setPosition(it->getPosition().x, 0);
            }
            for (auto it : anims)
            {
                it->Abort();
            }
            DoneCount = 0;
            AnimsClock.restart();
        }
    });
    ValDownPb.onClick.connect([this](bool down)
    {
        if (down)
        {
            if (pr.GetValue() <= pr.GetMinValue())
                pr.SetValue(0);
            else
            {
                pr.SetValue(pr.GetValue() - 10);
            }
            AnimsTime -= sf::seconds(0.5);
            for (auto it : shapes)
            {
                it->setPosition(it->getPosition().x, 0);
            }
            for (auto it : anims)
            {
                it->Abort();
            }
            DoneCount = 0;
            AnimsClock.restart();
        }
    });


    float TotalSize = 400;
    for (int i = 0; i < ShapesCount; ++i)
    {
        shapes.push_back(new RoundedRectangleShape());
        shapes[i]->setSize({TotalSize / (ShapesCount + 5), TotalSize / (ShapesCount + 5)});
        shapes[i]->setCornerRadius(shapes[i]->getSize().x / 4);
        shapes[i]->setFillColor({78, 119, 163});
        shapes[i]->setPosition((TotalSize / ShapesCount) * i, 0);
        shapesGr.add(shapes[i]);
    }

    anims.resize(shapes.size());
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        anims[i] = new MoveAnim();
    }
    DoneCount = 0;

    add(shapesGr);
}

void DebugScene::Resize(sf::Vector2f NewSize)
{
    DefaultView.setSize(NewSize);
    DefaultView.setCenter({NewSize.x / 2, NewSize.y / 2});

    sf::Vector2i pos(GetAlignedPosition(NewSize, {0, 0},
                                        {WidgetsGr.getBounds().getSize().x, WidgetsGr.getBounds().getSize().y},
                                        WidgetsGr.getPosition(), Aligns::RightCenter));
    WidgetsGr.setPosition(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));

    sf::Vector2i posMem(GetAlignedPosition(NewSize, {0, 0},
                                           MemGr.getBounds().getSize(),
                                           MemGr.getPosition(), Aligns::RightBottom));
    MemGr.setPosition({(float)posMem.x, (float)posMem.y});

    sf::Vector2i posFT(GetAlignedPosition(NewSize, {0, 0},
                                          FrameGr.getBounds().getSize(),
                                          FrameGr.getPosition(), Aligns::RightTop));
    FrameGr.setPosition({(float)posFT.x, (float)posFT.y});
    AnimsY = NewSize.y;
}

void DebugScene::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    MemGr.HandleEvent(event, window);
    FrameGr.HandleEvent(event, window);
    sf::Transform t = WidgetsGr.getTransform();
    ValUpPb.HandleEvent(event, window, &t);
    ValDownPb.HandleEvent(event, window, &t);
    pr.HandleEvent(event, window);
    dd.HandleEvent(event, window, &t);
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::S:
            StartAnims();
            break;
        }
    }
}

void DebugScene::StartAnims()
{
    for (int i = 0; i < shapes.size(); ++i)
    {
        if (anims[i]->IsFinished() || DoneCount == i)
        {
            anims[i]->Abort();
            shapes[i]->setPosition(shapes[i]->getPosition().x, 0);
            anims[i] = new MoveAnim;
            anims[i]->SetAnimationType(animType);
            anims[i]->SetDeltaTime(AnimsTime);
            anims[i]->SetMoveOffset({0, AnimsY - shapes[0]->getSize().x});
            anims[i]->SetObj(shapes[i]);
            anims[i]->Start();
        }
    }
    DoneCount++;
}

void DebugScene::AfterDraw()
{
    FrameGr.UpdateFrame();
    if (AnimsClock.getElapsedTime() >= AnimsDeltaTime)
    {
        StartAnims();
        AnimsClock.restart();
    }
}
