#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
    ValueChanged.connect([this](float val)
    {
        sf::Vector2f size = getBounds().getSize();
        float progress = (maxVal - minVal != 0) ? (val - minVal) / (maxVal - minVal) : 0.f;
        progress = std::clamp(progress, 0.f, 1.f);
        float width = size.x * progress;
        float height = size.y;
        curr.setSize({std::min(width, body.getSize().x), height});
        if (width >= 2 * DefaultCornerRadius)
            curr.setCornerRadius(DefaultCornerRadius);
        else
            curr.setCornerRadius(width / 2.f);
    });

    setSize(DefaultSize);

    body.setFillColor(DefaultBodyFillColor);
    body.setCornerRadius(DefaultCornerRadius);
    body.setOutlineThickness(DefaultOutlineThickness);

    curr.setFillColor(DefaulProgressFillColor);

    maskShape.setSize(DefaultSize);
    maskShape.setCornerRadius(DefaultCornerRadius);
    maskShape.setFillColor(sf::Color::White);

    add(body);
}

ProgressBar::~ProgressBar() {}

void ProgressBar::SetValue(float value)
{
    float clamped = std::clamp(value, minVal, maxVal);
    if (currentVal != clamped)
    {
        currentVal = clamped;
        ValueChanged.emit(currentVal);
    }
}

void ProgressBar::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
}

void ProgressBar::setSize(sf::Vector2f size)
{
    body.setSize(size);
    maskShape.setSize(size);
    maskRenderer.create((unsigned int)size.x, (unsigned int)size.y);

    float progress = (maxVal - minVal != 0) ? (currentVal - minVal) / (maxVal - minVal) : 0.f;
    float width = size.x * std::clamp(progress, 0.f, 1.f);
    curr.setSize({std::min(width,body.getSize().x), size.y});
    if (width >= 2 * DefaultCornerRadius)
        curr.setCornerRadius(DefaultCornerRadius);
    else
        curr.setCornerRadius(width / 2.f);

    if (size.x != 0 && size.y != 0)
        body.setOutlineThickness(DefaultOutlineThickness);
}

void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(body, states);

    sf::Vector2f size = body.getSize();
    maskShape.setSize(size);
    maskRenderer.setMask(maskShape);
    maskRenderer.drawMasked(curr);
    maskRenderer.display(target, getPosition());
}
