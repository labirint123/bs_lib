#include "ProgressBar.h"
#include "Log.h"

ProgressBar::ProgressBar()
{
    body.setFillColor(DefaultBodyFillColor);
    body.setOutlineThickness(DefaultOutlineThickness);

    curr.setFillColor(DefaulProgressFillColor);

    setSize(DefaultSize);
    curr.setCornerRadius(DefaultCornerRadius);
    body.setCornerRadius(DefaultCornerRadius);

    ValueChanged.connect([this](float val)
                         {
        float progress = (maxVal - minVal != 0.f)
            ? (val - minVal) / (maxVal - minVal)
            : 0.f;
        progress = std::clamp(progress, 0.f, 1.f);

        sf::Vector2f size = body.getSize();
        float fillWidth = std::clamp(size.x * progress, 0.f, size.x);
        float adaptiveRadius = std::min(DefaultCornerRadius, fillWidth / 2.f);

        curr.setSize({ fillWidth, size.y });
        curr.setCornerRadius(adaptiveRadius);
        curr.setPosition({ 0.f, 0.f });
        useMask = (fillWidth < DefaultCornerRadius * 2.f)
               || (fillWidth < DefaultCornerRadius * 2.f); });
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

void ProgressBar::setSize(sf::Vector2f size)
{
    body.setSize(size);
    maskShape.setSize(size);
    maskShape.setCornerRadius(DefaultCornerRadius);
    maskRenderer.create((unsigned int)size.x, (unsigned int)size.y);
    ValueChanged.emit(currentVal);
}

void ProgressBar::HandleEvent(const sf::Event &event, const sf::RenderWindow &window, sf::Transform* t) {}

void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!isVisible)
        return;
    states.transform *= getTransform();
    target.draw(body, states);

    if (useMask)
    {
        maskShape.setSize(body.getSize());
        maskShape.setCornerRadius(body.getTopLeftRadius());
        maskRenderer.setMask(maskShape);
        maskRenderer.drawMasked(curr);
        maskRenderer.display(target, states.transform.transformPoint({0, 0}));
    }
    else
    {
        target.draw(curr, states);
    }

    // RoundedRectangleShape border = body;
    // border.setFillColor(sf::Color::Transparent);
    // target.draw(border, states);
}
