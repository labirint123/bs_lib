#pragma once
#include <SFML/Graphics.hpp>
#include "Group.h"

class Widget : public Group
{
private:
    sf::View *view = nullptr;
public:
    void SetView(sf::View &view) { this->view = &view; }
    sf::View GetView() { return *view; }
    virtual void HandleEvent(const sf::Event &event, const sf::RenderWindow &window) = 0;
};