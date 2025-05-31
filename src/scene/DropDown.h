#pragma once
#include "Widget.h"
#include "RoundedRectangleShape.hpp"
#include "Item.h"
#include "signal.h"
#include "MoveAnim.h"

class DropDown : public Widget
{
protected:
    std::vector<std::pair<Item, sf::Text*>> Items;
    int SelectedItem = -1;

    std::string PlaseHolderString;

    sf::Vector2f Size{150, 30};
    unsigned int CharacterSize = 20;
    float OutlineThickness = 2;
    float CornerRadius = 10;
    sf::Color TextColor = sf::Color::White;
    sf::Color FillColor = sf::Color(50, 50, 50, 200);
    sf::Color DisabledFillColor = sf::Color(30, 30, 30, 200);
    sf::Color HoverFillColor = sf::Color(70, 70, 70, 200);
    sf::Color PressedFillColor = sf::Color(30, 30, 30, 200);

    sf::Font font;
    sf::Text BodyText;
    RoundedRectangleShape TopBody;
    RoundedRectangleShape BottomBody;
    Group BottomGroup;
    bool opend = 1;
    MoveAnim anim;
    Animation* animClone = nullptr;
    bool CanHandleEvents();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    void open();
    void close();
    bool isOpen() const;
    bool SelectItem(unsigned int index);
    void UpdateList();


    void SetPlaceHolderString(std::string str);
    void HandleEvent(const sf::Event &event, const sf::RenderWindow &window, sf::Transform* t = nullptr);
    void setFont(sf::Font &font);

    int AddItem(std::string str);
    bool RemoveItem(unsigned int index);
    int selected_item() const;
    int items_count() const;
    Signal<bool>& GetItemSignal(unsigned int index);
    DropDown();
};