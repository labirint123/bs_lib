#include "DropDown.h"
#include "bs.h"
#include "Utils.hpp"

DropDown::DropDown()
{
    TopBody.setSize(Size);
    TopBody.setCornerRadius(CornerRadius);
    TopBody.setFillColor(FillColor);
    TopBody.setOutlineThickness(OutlineThickness);

    BottomBody.setSize(Size);
    BottomBody.setCornerRadius(CornerRadius);
    BottomBody.setFillColor(FillColor);
    BottomBody.setOutlineThickness(OutlineThickness);
    BottomBody.setPosition({0, Size.y + OutlineThickness});

    SelectionHighlight.setSize(Size);
    SelectionHighlight.setCornerRadius(CornerRadius);
    SelectionHighlight.setFillColor(HoverFillColor);

    BodyText.setCharacterSize(CharacterSize);
    BodyText.setStyle(sf::Text::Bold);

    if (bs::DefaultFont)
    {
        font = *bs::DefaultFont;
        BodyText.setFont(font);
    }
    BottomGroup.add(BottomBody);

    anim.SetAnimationType(Animation::easeOutCubic);
    anim.SetDeltaTime(sf::seconds(0.1));
    anim.SetObj(&BottomGroup);
}

void DropDown::UpdateList()
{
    if (Items.empty() || SelectedItem == -1)
    {
        BodyText.setString(PlaseHolderString);
        Align(BodyText, TopBody, Aligns::Center);
    }
    else
    {
        BodyText.setString(Items[selected_item()].first.getString());
        Align(BodyText, TopBody, Aligns::Center);
    }

    BottomGroup.clear();
    BottomGroup.add(BottomBody);
    bool sel = 0;
    if (!Items.empty())
    {
        for (size_t i = 0; i < Items.size(); ++i)
        {
            if (selected_item() == i)
            {
                sel = 1;
            }
            auto& text = Items[i].second;
            auto& item = Items[i].first;
            if (!text)
            {
                text = new sf::Text;
                text->setCharacterSize(CharacterSize);
                text->setStyle(sf::Text::Bold);
                text->setFont(font);
            }
            text->setString(item.getString());
            if (selected_item() == i)
                text->setString("");

            sf::FloatRect b = text->getLocalBounds();
            text->setOrigin(
                std::round(b.left + b.width / 2.f),
                std::round(b.top + b.height / 2.f)
            );

            float innerW = Size.x - 2 * OutlineThickness;
            float off = OutlineThickness;
            float x = off + innerW / 2.f;
            float y = off + Size.y * (i + 1) + Size.y / 2.f;
            if (sel)
                y = off + Size.y * (i) + Size.y / 2.f;
            else
                y = off + Size.y * (i + 1) + Size.y / 2.f;

            text->setPosition(std::round(x), std::round(y));
            BottomGroup.add(*text);
        }
        if (SelectedItem == -1)
            BottomBody.setSize({Size.x, Size.y * Items.size()});
        else
            BottomBody.setSize({Size.x, Size.y * (Items.size() - 1)});

        BottomBody.setPosition(0, std::round(Size.y + OutlineThickness));
    }
    anim.SetObj(&BottomGroup);
}

int DropDown::selected_item() const
{
    return SelectedItem;
}

int DropDown::items_count() const
{
    return Items.size();
}

Signal<bool>& DropDown::GetItemSignal(unsigned int index)
{
    if (index >= Items.size())
    {
        Log("Signal<bool>& DropDown::GetItemSignal(unsigned int index)\nOut of Items range");
        throw("Signal<bool>& DropDown::GetItemSignal(unsigned int index)\nOut of Items range");
    }
    return Items[index].first.getSelectedSignal();
}

void DropDown::SetPlaceHolderString(std::string str)
{
    PlaseHolderString = str;
    UpdateList();
}

void DropDown::HandleEvent(const sf::Event& event, const sf::RenderWindow& window, sf::Transform* t)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, *view);
    sf::Vector2f mousePos = t ? t->getInverse().transformPoint(worldPos) : worldPos;

    // HOWER
    // TOP
    sf::Vector2f topLeft2{0.f, 0.f};
    sf::Vector2f bottomRight2 = {Size.x, Size.y};
    topLeft2 = this->getTransform().transformPoint(topLeft2);
    bottomRight2 = this->getTransform().transformPoint(bottomRight2);
    if (mousePos.x > topLeft2.x && mousePos.x < bottomRight2.x &&
        mousePos.y > topLeft2.y && mousePos.y < bottomRight2.y)
        TopBody.setFillColor(HoverFillColor);
    else
        TopBody.setFillColor(FillColor);
    // BOTTOM
    {
        bool sel = 0;
        for (int i = 0; i < Items.size(); ++i)
        {
            if (selected_item() == i)
            {
                sel = 1;
                continue;
            }
            sf::Vector2f topLeft{0.f, Size.y * (i + 1) + OutlineThickness};
            sf::Vector2f bottomRight{Size.x, Size.y * (i + 2) + OutlineThickness};

            if (sel)
            {
                topLeft = {0.f, Size.y * (i) + OutlineThickness};
                bottomRight = {Size.x, Size.y * (i + 1) + OutlineThickness};
            }

            topLeft = this->getTransform().transformPoint(topLeft);
            bottomRight = this->getTransform().transformPoint(bottomRight);

            if (mousePos.x > topLeft.x && mousePos.x < bottomRight.x &&
                mousePos.y > topLeft.y && mousePos.y < bottomRight.y)
            {
                sf::Vector2f topLeftPrev{0.f, Size.y * (i + 1) + OutlineThickness};
                if (sel)
                    topLeftPrev = {0.f, Size.y * (i) + OutlineThickness};
                SelectionHighlight.setPosition(topLeftPrev);
                DrawHighLight = 1;
                break;
            }
            else
            {
                DrawHighLight = 0;
            }
        }
    }


    // CLICK

    if (Items.empty())
        return;


    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
    {
        if (CanHandleEvents())
        {
            bool sel = 0;
            for (int i = 0; i < Items.size(); ++i)
            {
                if (selected_item() == i)
                {
                    sel = 1;
                    continue;
                }
                sf::Vector2f topLeft{0.f, Size.y * (i + 1) + OutlineThickness};
                sf::Vector2f bottomRight{Size.x, Size.y * (i + 2) + OutlineThickness};

                if (sel)
                {
                    topLeft = {0.f, Size.y * (i) + OutlineThickness};
                    bottomRight = {Size.x, Size.y * (i + 1) + OutlineThickness};
                }

                topLeft = this->getTransform().transformPoint(topLeft);
                bottomRight = this->getTransform().transformPoint(bottomRight);

                if (mousePos.x > topLeft.x && mousePos.x < bottomRight.x &&
                    mousePos.y > topLeft.y && mousePos.y < bottomRight.y)
                {
                    if (selected_item() >= 0)
                        Items[selected_item()].first.getSelectedSignal().emit(false);
                    SelectItem(i);
                    Items[i].first.getSelectedSignal().emit(true);
                    break;
                }
            }
        }

        sf::Vector2f topLeft2{0.f, 0.f};
        sf::Vector2f bottomRight2 = {Size.x, Size.y};
        topLeft2 = this->getTransform().transformPoint(topLeft2);
        bottomRight2 = this->getTransform().transformPoint(bottomRight2);
        if (mousePos.x > topLeft2.x && mousePos.x < bottomRight2.x &&
            mousePos.y > topLeft2.y && mousePos.y < bottomRight2.y)
        {
            if (opend)
                close();
            else
                open();
        }
    }
}

void DropDown::setFont(sf::Font& font)
{
    this->font = font;
    BodyText.setFont(font);
    for (auto& item : Items)
    {
        item.second->setFont(font);
    }
}

int DropDown::AddItem(std::string str)
{
    this->Items.push_back({Item(str), nullptr});
    UpdateList();
    return Items.size() - 1;
}

bool DropDown::RemoveItem(unsigned int index)
{
    Log("hi");
    return 1;
}

bool DropDown::CanHandleEvents()
{
    return opend;
}

void DropDown::open()
{
    if (animClone != nullptr)
    {
        animClone->Abort();
    }
    sf::Vector2f finalPos = {0, 0};
    sf::Vector2f DeltaMove = finalPos - BottomGroup.getPosition();
    anim.SetMoveOffset(DeltaMove);
    anim.SetObj(&BottomGroup);
    animClone = anim.StartClone();

    Log("Open");
    opend = 1;
}

void DropDown::close()
{
    if (animClone != nullptr)
    {
        animClone->Abort();
    }
    sf::Vector2f finalPos = {0, 0 - BottomBody.getSize().y - TopBody.getSize().y - OutlineThickness * 2};
    sf::Vector2f DeltaMove = finalPos - BottomGroup.getPosition();
    anim.SetMoveOffset(DeltaMove);
    anim.SetObj(&BottomGroup);
    animClone = anim.StartClone();

    Log("Close");
    opend = 0;
}

bool DropDown::isOpen() const
{
    return opend;
}

bool DropDown::SelectItem(unsigned int index)
{
    if (index >= Items.size())
        return false;

    this->SelectedItem = index;
    UpdateList();
    return true;
}


void DropDown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isVisible)
        return;
    states.transform *= getTransform();
    sf::RenderStates prevStates = states;

    if (Items.size() > 0 && (opend || (animClone && animClone->IsStarted() && !animClone->IsAborted())))
    {
        if (animClone && animClone->IsStarted() && !animClone->IsAborted())
        {
            float halfTop = Size.y / 2.f;
            float newBoundary = halfTop;
            float bottomHeight = BottomBody.getSize().y;
            unsigned texW = static_cast<unsigned>(std::ceil(Size.x + 2 * OutlineThickness));
            unsigned texH = static_cast<unsigned>(std::ceil(bottomHeight + halfTop));

            static sf::RenderTexture clipTexture;
            static sf::Vector2u lastSize{0, 0};
            if (lastSize.x != texW || lastSize.y != texH)
            {
                clipTexture.create(texW, texH);
                lastSize = {texW, texH};
            }

            clipTexture.clear(sf::Color::Transparent);

            sf::View clipView(sf::FloatRect(-OutlineThickness, newBoundary, (float)texW, (float)texH));
            clipTexture.setView(clipView);

            sf::RenderStates rs;
            rs.transform = BottomGroup.getTransform();

            for (auto item : BottomGroup.Shapes)
                clipTexture.draw(*item, rs);

            if (DrawHighLight)
                clipTexture.draw(SelectionHighlight, rs);

            for (auto item : BottomGroup.Texts)
                clipTexture.draw(*item, rs);

            clipTexture.display();

            sf::Sprite sprite(clipTexture.getTexture());
            sprite.setPosition(-OutlineThickness, newBoundary);
            target.draw(sprite, states);
        }
        else
        {
            states.transform *= BottomGroup.getTransform();
            for (auto item : BottomGroup.Shapes)
                target.draw(*item, states);
            if (DrawHighLight)
                target.draw(SelectionHighlight, states);
            for (auto item : BottomGroup.Texts)
                target.draw(*item, states);
        }
    }

    target.draw(TopBody, prevStates);
    target.draw(BodyText, prevStates);
}
