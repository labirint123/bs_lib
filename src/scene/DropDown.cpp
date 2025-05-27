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
                std::round(bounds.left + bounds.width / 2.f),
                std::round(bounds.top + bounds.height / 2.f)
            );


            float posX = std::round(Size.x / 2.f);
            float posY = std::round(Size.y * (index + 1) + Size.y / 2.f);
            text->setPosition(posX, posY);

            ++index;
        }

        BottomBody.setSize({Size.x, Size.y * Items.size()});
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

        for (int i = 0; i < Items.size(); ++i)
        {
            sf::Vector2f topLeft{0.f, Size.y * (i + 1)};
            sf::Vector2f bottomRight{Size.x, Size.y * (i + 2)};
            topLeft = this->getTransform().transformPoint(topLeft);
            bottomRight = this->getTransform().transformPoint(bottomRight);

            if (mousePos.x > topLeft.x && mousePos.x < bottomRight.x &&
                mousePos.y > topLeft.y && mousePos.y < bottomRight.y)
            {
                Items[i].first.getSelectedSignal().emit(true); // Код верный
                break;
            }
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
