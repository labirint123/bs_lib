#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Parameter
{
    std::string name;
    float value = 0;
    sf::Color color = sf::Color::White;
    std::vector<std::pair<float, float>> history;
};

class DebugInfoUi : public sf::Drawable
{
public:
    DebugInfoUi();

    void SetFont(const sf::Font &font);

    int AddParameter(Parameter &p);

    void SetTimeWindow(float seconds) { m_timeWindow = seconds; }

    void Update();

private:
    struct Element
    {
        Parameter *param = nullptr;
        sf::Text label;
        sf::Text valueText;
        sf::RectangleShape graphBg;
    };

    std::vector<Element> m_elements;
    sf::Font m_font;
    sf::Clock m_clock;
    float m_timeWindow = 5.f;
    float m_margin = 5.f;
    float m_graphHeight = 50.f;
    float m_graphWidth = 200.f;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
