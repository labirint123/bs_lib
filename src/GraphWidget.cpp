#include "GraphWidget.h"
#include "Utils.hpp"

void GraphWidget::SetFont(sf::Font &font)
{
    this->font = font;
    Label.setFont(font);
    ValText.setFont(font);
    Label.setPosition(0, 0);
    ValText.setPosition(GetSize(Label).x + 10, 0);
}

void GraphWidget::SetTimeWindow(float TimeWindow)
{
    this->TimeWindow = TimeWindow;
}

void GraphWidget::SetGraphColor(sf::Color color)
{
    this->color = color;
    Label.setColor(color);
    ValText.setColor(color);
}

void GraphWidget::SetLabel(std::string label)
{
    this->Label.setString(label);
    ValText.setPosition(GetSize(Label).x + 10, 0);
}

void GraphWidget::Update(float value)
{
    sf::Time delt = this->lastUpdate.restart();
    history.push_back({value, delt});

    sf::Time sum = sf::seconds(0);
    int cutIndex = -1;

    for (int i = history.size() - 1; i >= 0; --i)
    {
        sum += history[i].second;
        if (sum > sf::seconds(TimeWindow))
        {
            cutIndex = i;
            break;
        }
    }

    if (cutIndex > 0)
    {
        history.erase(history.begin(), history.begin() + cutIndex);
    }

    this->ValText.setString(std::to_string(value));

    float min;
    float max;
    for (size_t i = 0; i < history.size(); i++)
    {
        if (i == 0)
        {
            min = max = history[i].first;
            continue;
        }
        min = std::min(history[i].first, min);
        max = std::max(history[i].first, max);
    }
    minVal = min - std::abs(min / 2);
    maxVal = max + std::abs(max / 2);
}

void GraphWidget::draw(sf::RenderTarget &target, sf::RenderStates states)
{
    states.transform *= getTransform();
    for (auto d : drawables)
        target.draw(*d, states);

    sf::VertexArray polyline(sf::LineStrip, history.size());

    
    float width = Size.x;
    float height = Size.y - GetSize(Label).y - 10;
    sf::Time activeTiming = sf::seconds(0);

    for (size_t i = 0; i < history.size(); ++i)
    {
        activeTiming += history[i].second;
        polyline[i].position = sf::Vector2f(width * activeTiming.asSeconds() / TimeWindow, 40.f);

        polyline[i].color = sf::Color::Red; 
    }
    target.draw(polyline,states);

}

GraphWidget::GraphWidget()
{
    add(bg);
    add(Label);
    add(ValText);
    ValText.setStyle(sf::Text::Bold);
    bg.setSize(Size);
    bg.setFillColor(sf::Color(20, 20, 20, 100));
}
