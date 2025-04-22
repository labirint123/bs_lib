#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "Group.h"
#include "Animation.h"

class GraphWidget : public Group
{
public:
    GraphWidget();

    void SetFont(sf::Font &font);
    void SetTimeWindow(float seconds);
    void SetGraphColor(sf::Color color);
    void SetLabel(const std::string &label);
    void Update();
    void SetValue(float &value);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void ClearData();
private:
    sf::Clock lastUpdate;
    float *value;
    void rebuildPolyline() const;

    std::deque<std::pair<float, sf::Time>> history;
    size_t maxPoints = 1000;
    float TimeWindow = 5.f;

    sf::Time sampleAccum = sf::seconds(0.f);
    sf::Time sampleInterval = sf::seconds(1.f / 60.f);

    mutable bool dirty = true;

    sf::Font font;
    sf::Color color = sf::Color::White;

    sf::RectangleShape bg;
    sf::Text Label;
    sf::Text ValText;
    sf::Vector2f Size = {400.f, 100.f};

    float minVal = 0.f, maxVal = 1.f;
    float cachedLabelHeight = 0.f;

    mutable sf::VertexArray cachedPolyline;
};
