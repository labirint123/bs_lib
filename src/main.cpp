#include <SFML/Graphics.hpp>
#include "RectHitbox.h"
#include "CircleHitbox.h"
#include "PolygonHitbox.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hitbox Test");
    window.setFramerateLimit(60);

    RectHitbox rect({100, 100}, {120, 80});
    CircleHitbox circle({400, 300}, 60);

    std::vector<sf::Vector2f> tri = {
        {600, 400}, {700, 350}, {750, 450}, {750, 750}, {320, 450}};
    PolygonHitbox polygon(tri);

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            rect.setPosition(rect.getPosition() + sf::Vector2f(-3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            rect.setPosition(rect.getPosition() + sf::Vector2f(3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rect.setPosition(rect.getPosition() + sf::Vector2f(0, -3));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rect.setPosition(rect.getPosition() + sf::Vector2f(0, 3));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            circle.setPosition(circle.getPosition() + sf::Vector2f(-3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            circle.setPosition(circle.getPosition() + sf::Vector2f(3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            circle.setPosition(circle.getPosition() + sf::Vector2f(0, -3));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            circle.setPosition(circle.getPosition() + sf::Vector2f(0, 3));

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        bool rectVsCircle = rect.intersects(circle) || circle.intersects(rect);
        bool rectVsPoly = rect.intersects(polygon) || polygon.intersects(rect);
        bool circleVsPoly = circle.intersects(polygon) || polygon.intersects(circle);

        bool cursorInRect = rect.contains(mousePos);
        bool cursorInCircle = circle.contains(mousePos);
        bool cursorInPoly = polygon.contains(mousePos);

        window.clear(sf::Color::Black);
        rect.draw(window, rectVsCircle || rectVsPoly || cursorInRect);
        circle.draw(window, rectVsCircle || circleVsPoly || cursorInCircle);
        polygon.draw(window, rectVsPoly || circleVsPoly || cursorInPoly);
        window.display();
    }

    return 0;
}
