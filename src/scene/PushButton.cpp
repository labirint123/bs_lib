#include "PushButton.h"
#include "bs.h"
#include "Log.h"

PushButton::PushButton()
{
    this->onBoundsChanged.connect([this]()
                                  {
        updateHitbox();
        Align(Text, base, Aligns::Center); });

    setDefaultSignalBehavior(true);

    if (bs::DefaultFont != nullptr)
        setFont(*bs::DefaultFont);

    setCharacterSize(DefaultCharacterSize);
    setOutlineThickness(DefaultOutlineThickness);
    setTextColor(DefaultTextColor);
    setFillColor(DefaultFillColor);
    setSize(DefaultSize);
    setCornerRadius(DefaultCornerRadius);
    Text.setStyle(sf::Text::Bold);
    add(base);
    add(Text);
}

PushButton::~PushButton()
{
    delete mHitbox;
    mHitbox = nullptr;
}

void PushButton::updateHitbox()
{
    sf::Transform tr = getTransform();
    auto points = GetTransformedPoints(&base, tr);

    if (mHitbox)
        *mHitbox = PolygonHitbox(points);
    else
        mHitbox = new PolygonHitbox(points);
}

void PushButton::setSize(sf::Vector2f size)
{
    base.setSize(size);
    Align(Text, base, Aligns::Center);
    onBoundsChanged.emit();
}

void PushButton::setFillColor(const sf::Color &color)
{
    base.setFillColor(color);
}

void PushButton::setOutlineColor(const sf::Color &color)
{
    base.setOutlineColor(color);
}

void PushButton::setOutlineThickness(float thickness)
{
    base.setOutlineThickness(thickness);
}

void PushButton::setTextColor(const sf::Color &color)
{
    Text.setFillColor(color);
}

void PushButton::setFont(const sf::Font &font)
{
    Text.setFont(font);
    Align(Text, base, Aligns::Center);
}

void PushButton::setCharacterSize(unsigned int size)
{
    Text.setCharacterSize(size);
    Align(Text, base, Aligns::Center);
}

void PushButton::setCornerRadius(unsigned int radius)
{
    base.setCornerRadius(radius);
    onBoundsChanged.emit();
}

void PushButton::setText(std::string text)
{
    Text.setString(text);
    Align(Text, base, Aligns::Center);
}

sf::Vector2f PushButton::getSize() const
{
    return base.getSize();
}

sf::Text PushButton::GetText() const
{
    return Text;
}

std::string PushButton::GetString() const
{
    return Text.getString().toAnsiString();
}

RoundedRectangleShape PushButton::GetBase() const
{
    return base;
}

void PushButton::HandleEvent(const sf::Event &event, const sf::RenderWindow &window)
{
    if (!view || !mHitbox || !IsEnabled)
        return;

    if (!IsEnabled) Log("hi");
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), *view);
    bool nowHovered = mHitbox->contains(mousePos);

    if (nowHovered != isHovered)
    {
        isHovered = nowHovered;
        // Log(std::string("Hovered: ") + (isHovered ? "true" : "false"));
        onHovered.emit(isHovered);
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        if (isHovered)
        {
            isPressed = true;
            // Log("Click: true");
            onClick.emit(true);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        // Log("Release");
        onRelease.emit(true);

        if (isPressed && isHovered)
        {
            // Log("Click: false");
            onClick.emit(false);
        }

        isPressed = false;
    }

    if (isPressed && isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Log("Hold");
        onHold.emit(true);
    }
}

void PushButton::setDefaultSignalBehavior(bool enable)
{
    if (enable && !IsDefaultSignalsEnabled)
    {
        onHoveredDefId = onHovered.connect([this](bool hover)
        {
            base.setFillColor(hover ? HoverFillColor : DefaultFillColor);
        });

        onClickDefId = onClick.connect([this](bool down)
        {
            base.setFillColor(down ? PressedFillColor : HoverFillColor);
        });

        onReleaseDefId = onRelease.connect([this](bool)
        {
            base.setFillColor(DefaultFillColor);
        });

        onEnabledDefId = onEnabled.connect([this](bool enabled)
        {
            base.setFillColor(enabled
                ? DefaultFillColor
                : DefaultDisabledFillColor);
        });

        IsDefaultSignalsEnabled = true;
    }
    else if (!enable && IsDefaultSignalsEnabled)
    {
        onHovered.disconnect(onHoveredDefId);
        onClick.disconnect(onClickDefId);
        onRelease.disconnect(onReleaseDefId);
        onEnabled.disconnect(onEnabledDefId);
        IsDefaultSignalsEnabled = false;
    }
}
void PushButton::SetEnabled(bool Enabled)
{
    this->IsEnabled = Enabled;
    this->onEnabled.emit(Enabled);
}
