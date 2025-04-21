#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Group.h"

class GraphWidget : public Group
{
private:
    sf::Font font;
    float TimeWindow;
    std::vector<std::pair<float, sf::Time>> history;
    sf::Color color = sf::Color::White;
    sf::Clock lastUpdate;

    sf::RectangleShape bg;
    sf::Text Label;
    sf::Text ValText;

    sf::Vector2f Size = {400,300};
    float minVal = 0;
    float maxVal = 0;

public:
    void SetFont(sf::Font &font);
    void SetTimeWindow(float TimeWindow);
    void SetGraphColor(sf::Color color);
    void SetLabel(std::string label);

    void Update(float value);

    void draw(sf::RenderTarget &target, sf::RenderStates states);
    GraphWidget();
};
