#include "DebugInfoUi.h"

DebugInfoUi::DebugInfoUi()
{
}

void DebugInfoUi::SetFont(const sf::Font &font)
{
    m_font = font;

    for (auto &e : m_elements)
    {
        e.label.setFont(m_font);
        e.valueText.setFont(m_font);
    }
}

int DebugInfoUi::AddParameter(Parameter &p)
{
    Element e;
    e.param = &p;
    e.label = sf::Text(p.name, m_font, 14);
    e.valueText = sf::Text("", m_font, 14);

    e.label.setFillColor(sf::Color::White);
    e.valueText.setFillColor(p.color);

    e.graphBg.setFillColor(sf::Color(0, 0, 0, 120));

    m_elements.push_back(e);
    return int(m_elements.size()) - 1;
}

void DebugInfoUi::Update()
{
    float now = m_clock.getElapsedTime().asSeconds();
    float yOffset = 0.f;

    for (auto &e : m_elements)
    {

        e.param->history.emplace_back(now, e.param->value);

        while (!e.param->history.empty() && now - e.param->history.front().first > m_timeWindow)
        {
            e.param->history.erase(e.param->history.begin());
        }

        e.valueText.setString(" = " + std::to_string(e.param->value));

        e.label.setPosition(0.f, yOffset);
        e.valueText.setPosition(
            e.label.getLocalBounds().width + 10.f,
            yOffset);

        float textHeight = e.label.getLocalBounds().height;

        float graphTop = yOffset + textHeight + 5.f;
        e.graphBg.setPosition(0.f, graphTop);
        e.graphBg.setSize({m_graphWidth, m_graphHeight});

        yOffset = graphTop + m_graphHeight + 15.f;
    }
}

void DebugInfoUi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(10.f, 10.f);

    float now = m_clock.getElapsedTime().asSeconds();
    float yOffset = 0.f;

    for (auto &e : m_elements)
    {
        target.draw(e.label, states);
        target.draw(e.valueText, states);
        target.draw(e.graphBg, states);

        std::vector<sf::Vertex> verts;
        float minV = 1e9f, maxV = -1e9f;
        for (auto &pt : e.param->history)
        {
            minV = std::min(minV, pt.second);
            maxV = std::max(maxV, pt.second);
        }
        if (minV == maxV)
        {
            minV -= 1.f;
            maxV += 1.f;
        }

        for (auto &pt : e.param->history)
        {
            float t = pt.first;
            float v = pt.second;
            float xNorm = (t - (now - m_timeWindow)) / m_timeWindow;
            if (xNorm < 0.f || xNorm > 1.f)
                continue;
            float yNorm = (v - minV) / (maxV - minV);

            float x = e.graphBg.getPosition().x + xNorm * m_graphWidth;
            float y = e.graphBg.getPosition().y + (1.f - yNorm) * m_graphHeight;
            verts.emplace_back(sf::Vector2f(x, y), e.param->color);
        }

        if (verts.size() >= 2)
            target.draw(&verts[0], verts.size(), sf::LineStrip, states);

        yOffset = e.graphBg.getPosition().y + m_graphHeight + 15.f;
        states.transform = sf::Transform::Identity;
        states.transform.translate(10.f, 10.f + yOffset);
    }
}
