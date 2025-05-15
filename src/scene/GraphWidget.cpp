#include "GraphWidget.h"
#include "Utils.hpp"
#include <algorithm>
#include "bs.h"

GraphWidget::GraphWidget()
{
    bg.setSize(Size);
    bg.setFillColor(sf::Color(20, 20, 20, 100));

    ValText.setStyle(sf::Text::Bold);

    add(bg);
    add(Label);
    add(ValText);
    if (bs::DefaultFont)    this->SetFont(*bs::DefaultFont);
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

void GraphWidget::Update()
{
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

void GraphWidget::SetValue(float &value)
{
    this->value = &value;
}

void GraphWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
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
    this->history.clear();
}

void GraphWidget::rebuildPolyline() const
{
    size_t n = history.size();
    cachedPolyline = sf::VertexArray(sf::LineStrip, n);

    float w = Size.x;
    float h = Size.y - cachedLabelHeight - 5.f;
    float range = maxVal - minVal;
    if (range <= 0.f)
        range = 1.f;

    sf::Time total = sf::seconds(0);
    for (auto &p : history)
        total += p.second;

    sf::Time acc = sf::seconds(0);

    for (size_t i = 0; i < n; ++i)
    {
        acc += history[i].second;
        float timestamp = acc.asSeconds();

        float x;
        if (total.asSeconds() < TimeWindow)
        {
            x = w * (timestamp / TimeWindow);
        }
        else
        {
            float startOffset = total.asSeconds() - TimeWindow;
            x = w * ((timestamp - startOffset) / TimeWindow);
        }

        float norm = (history[i].first - minVal) / range;
        float y = h * (1.f - norm) + cachedLabelHeight + 5.f;

        cachedPolyline[i].position = {x, y};
        cachedPolyline[i].color = color;
    }

    dirty = false;
}
