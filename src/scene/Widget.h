#pragma once
#include <SFML/Graphics.hpp>
#include "Group.h"

class Widget : public Group
{
protected:
    sf::View *view = nullptr;
    bool isVisible = 1;

public:
    void SetVisibility(bool IsVisible) { this->isVisible = IsVisible; }
    bool IsVisible() { return this->isVisible; }
    void SetView(sf::View &view) { this->view = &view; }
    sf::View GetView() { return *view; }
    virtual void HandleEvent(const sf::Event &event, const sf::RenderWindow &window) = 0;
};