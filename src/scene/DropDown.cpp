#include "DropDown.h"

DropDown::DropDown()
{
    TopBody.setSize(DefaultSize);
    TopBody.setCornerRadius(DefaultCornerRadius);
    TopBody.setFillColor(DefaultFillColor);

}

void DropDown::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
if (!isVisible)
        return;
    states.transform *= getTransform();
    target.draw(TopBody, states);
}

void DropDown::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
}
