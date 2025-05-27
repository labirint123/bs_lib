#include "GraphWidget.h"
#include "Utils.hpp"
#include <algorithm>
#include "bs.h"

GraphWidget::GraphWidget()
    : cachedPolyline(sf::LineStrip)
{
    cachedPolyline.resize(maxPoints);

    bg.setSize(Size);
    bg.setFillColor(sf::Color(10, 10, 10, 100));
    ValText.setStyle(sf::Text::Bold);

    add(bg);
    add(Label);
    add(ValText);

    if (bs::DefaultFont)
        SetFont(*bs::DefaultFont);
}

void GraphWidget::SetFont(sf::Font &f)
{
    font = f;
    Label.setFont(font);
    ValText.setFont(font);
    Label.setPosition(0.f, 0.f);
    ValText.setPosition(GetSize(Label).x + 10, 0.f);
    cachedLabelHeight = GetSize(Label).y;
}

void GraphWidget::SetTimeWindow(float seconds)
{
    TimeWindow = seconds;
}

void GraphWidget::SetGraphColor(sf::Color c)
{
    color = c;
    Label.setFillColor(c);
    ValText.setFillColor(c);
}

void GraphWidget::SetLabel(const std::string &s)
{
    Label.setString(s);
    cachedLabelHeight = GetSize(Label).y;
    ValText.setPosition(GetSize(Label).x + 10, 0.f);
}

void GraphWidget::SetValue(float &v)
{
    value = &v;
}

void GraphWidget::SetSize(const sf::Vector2f &size)
{
    Size = size;
    bg.setSize(Size);
    dirty = true;
}

void GraphWidget::Update()
{
    if (!value)
        return;

    sf::Time dt = lastUpdate.restart();
    if (dt == sf::Time::Zero)
        return;

    sampleAccum += dt;
    if (sampleAccum < sampleInterval)
        return;
    dt = sampleAccum;
    sampleAccum = sf::seconds(0.f);

    history.emplace_back(*value, dt);

    sf::Time sum = sf::seconds(0);
    for (auto it = history.rbegin(); it != history.rend(); ++it)
    {
        sum += it->second;
        if (sum > sf::seconds(TimeWindow))
            break;
    }
    while (!history.empty() && sum > sf::seconds(TimeWindow))
    {
        sum -= history.front().second;
        history.pop_front();
    }

    while (history.size() > maxPoints)
        history.pop_front();

    ValText.setString(std::to_string(*value));

    if (!history.empty())
    {
        minVal = maxVal = history.front().first;
        for (auto &p : history)
        {
            minVal = std::min(minVal, p.first);
            maxVal = std::max(maxVal, p.first);
        }
        float range = maxVal - minVal;
        if (range <= 0.f)
        {
            minVal -= 1.f;
            maxVal += 1.f;
        }
        else
        {
            minVal -= std::abs(minVal / 5.f);
            maxVal += std::abs(maxVal / 5.f);
        }
    }

    dirty = true;
}

void GraphWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!this->isVisible)
        return;
    states.transform *= getTransform();
    for (auto d : drawables)
        target.draw(*d, states);

    if (history.empty())
        return;

    if (dirty)
        rebuildPolyline();

    target.draw(cachedPolyline, states);
}

void GraphWidget::ClearData()
{
    history.clear();
    dirty = true;
}

void GraphWidget::HandleEvent(const sf::Event &event, const sf::RenderWindow &window, sf::Transform* t)
{
    if (!IsMovable)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(
        (event.type == sf::Event::MouseMoved)
            ? sf::Mouse::getPosition(window)
            : sf::Vector2i(event.mouseButton.x, event.mouseButton.y),
        *this->view);

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        if (this->getBounds().contains(mousePos))
        {
            IsMouseHold = true;
            PrewMousePos = mousePos;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left)
    {
        IsMouseHold = false;
    }

    if (IsMouseHold)
    {
        sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), *this->view);
        sf::Vector2f delta = newMousePos - PrewMousePos;
        this->move(delta);
        PrewMousePos = newMousePos;
    }
}

void GraphWidget::rebuildPolyline() const
{
    size_t n = history.size();

    cachedPolyline.resize(n);

    float w = Size.x;
    float h = Size.y - cachedLabelHeight - 5.f;
    float range = maxVal - minVal;
    if (range <= 0.f)
        range = 1.f;

    sf::Time total = sf::seconds(0);
    for (auto &p : history)
        total += p.second;

    sf::Time acc = sf::seconds(0);
    size_t i = 0;
    for (auto &p : history)
    {
        acc += p.second;
        float t = acc.asSeconds();

        float x = (total.asSeconds() < TimeWindow)
                      ? w * (t / TimeWindow)
                      : w * ((t - (total.asSeconds() - TimeWindow)) / TimeWindow);

        float norm = (p.first - minVal) / range;
        float y = h * (1.f - norm) + cachedLabelHeight + 5.f;

        cachedPolyline[i].position = {x, y};
        cachedPolyline[i].color = color;
        ++i;
    }

    dirty = false;
}
