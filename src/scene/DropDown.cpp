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
    BottomBody.setPosition({0, Size.y});

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

    if (!Items.empty())
    {
        size_t index = 0;
        for (auto& item_r : Items)
        {
            auto& text = item_r.second;
            auto& item = item_r.first;

            if (text == nullptr)
            {
                text = new sf::Text;
                text->setCharacterSize(CharacterSize);
                text->setStyle(sf::Text::Bold);
                text->setFont(font);
            }
            text->setString(item.getString());

            sf::FloatRect bounds = text->getLocalBounds();
            text->setOrigin(
                std::round(bounds.left + bounds.width  / 2.f),
                std::round(bounds.top  + bounds.height / 2.f)
            );


            float posX = std::round(Size.x / 2.f);
            float posY = std::round(Size.y * (index + 1) + Size.y / 2.f);
            text->setPosition(posX, posY);

            ++index;
        }

        BottomBody.setSize({ Size.x, Size.y * Items.size() });
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

void DropDown::SetPlaceHolderString(std::string str)
{
    PlaseHolderString = str;
    UpdateList();
}

void DropDown::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
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

int DropDown::AddItem(Item& item)
{
    this->Items.push_back({item, nullptr});
    UpdateList();
    return Items.size();
}

int DropDown::AddItem(std::string str, Signal<bool>& selected)
{
    this->Items.push_back({Item(selected, str), nullptr});
    UpdateList();
    return Items.size();
}

void DropDown::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isVisible)
        return;
    states.transform *= getTransform();
    target.draw(TopBody, states);
    target.draw(BodyText, states);
    if (Items.size() > 0)
    {
        target.draw(BottomBody, states);
        for (auto item : Items)
        {
            target.draw(*item.second, states); // кидает исключение при Items.size() > 0
        }
    }
}
