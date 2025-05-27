#include "DropDown.h"
#include "bs.h"

DropDown::DropDown()
{
    TopBody.setSize(Size);
    TopBody.setCornerRadius(CornerRadius);
    TopBody.setFillColor(FillColor);
    TopBody.setOutlineThickness(OutlineThickness);

    if (bs::DefaultFont)
    {
        font = *bs::DefaultFont;
        BodyText.setFont(font);
    }
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

void DropDown::setFont(sf::Font font)
{
    this->font = font;
    BodyText.setFont(font);
}
