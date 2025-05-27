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

    BodyText.setCharacterSize(CharacterSize);
    BodyText.setStyle(sf::Text::Bold);

    if (bs::DefaultFont)
    {
        font = *bs::DefaultFont;
        BodyText.setFont(font);
    }
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

    if (!Items.empty())
    {
        for (size_t i = 0; i < Items.size(); ++i)
        {
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

            sf::FloatRect b = text->getLocalBounds();
            text->setOrigin(
                std::round(b.left + b.width / 2.f),
                std::round(b.top + b.height / 2.f)
            );

            float innerW = Size.x - 2 * OutlineThickness;
            float off = OutlineThickness;
            float x = off + innerW / 2.f;
            float y = off + Size.y * (i + 1) + Size.y / 2.f;
            text->setPosition(std::round(x), std::round(y));
        }

        BottomBody.setSize({Size.x, Size.y * Items.size()});
        BottomBody.setPosition(0, std::round(Size.y + OutlineThickness));
    }
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
    if (Items.empty())
        return;

    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, *view);

        sf::Vector2f mousePos = t ? t->getInverse().transformPoint(worldPos) : worldPos;

        if (CanHandleEvents())
        {
            for (int i = 0; i < Items.size(); ++i)
            {
                sf::Vector2f topLeft{0.f, Size.y * (i + 1) + OutlineThickness};
                sf::Vector2f bottomRight{Size.x, Size.y * (i + 2) + OutlineThickness};
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
        sf::Vector2f topLeft2{0.f, 0.f + OutlineThickness};
        sf::Vector2f bottomRight2 = {Size.x, Size.y + OutlineThickness};
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
    // anim
    return opend;
}

void DropDown::open()
{
    opend = 1;
    // anim
}

void DropDown::close()
{
    opend = 0;
    // anim
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
    target.draw(TopBody, states);
    target.draw(BodyText, states);
    // anim
    if (Items.size() > 0 && opend)
    {
        target.draw(BottomBody, states);
        for (auto item : Items)
        {
            target.draw(*item.second, states);
        }
    }
}
