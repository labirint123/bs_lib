#include "ProgressBar.h"
#include "Log.h"

ProgressBar::ProgressBar()
{
    ValueChanged.connect([this](float val)
                         {
                             sf::Vector2f size = this->getBounds().getSize();

                             float progress = (maxVal - minVal != 0) ? (val - minVal) / (maxVal - minVal) : 0.f;
                             progress = std::clamp(progress, 0.f, 1.f);

                             float width = std::min(size.x * progress,DefaultSize.x);
                             float height = std::min(size.y, DefaultSize.y);

                             curr.setSize({width, height});
                             if (width != 0 && height != 0)
                                curr.setCornerRadius(DefaultCornerRadius);
                            Log(width);
                            Log(height);
                         });

    setSize(DefaultSize);

    body.setFillColor(DefaultBodyFillColor);
    body.setCornerRadius(DefaultCornerRadius);
    body.setOutlineThickness(DefaultOutlineThickness);

    curr.setFillColor(DefaulProgressFillColor);
    add(body);
    add(curr);
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

    float progress = (maxVal - minVal != 0) ? (currentVal - minVal) / (maxVal - minVal) : 0.f;
    progress = std::clamp(progress, 0.f, 1.f);

    curr.setSize({size.x * progress, size.y});

    if (size.x != 0 && size.y != 0)
        body.setOutlineThickness(DefaultOutlineThickness);
}
