#pragma once
#include <SFML/Graphics.hpp>

class ShapeMaskRenderer {
private:
    sf::RenderTexture maskTexture;
    sf::RenderTexture contentTexture;
    sf::Shader maskShader;
    sf::Vector2u size;
    sf::Sprite result;

    bool initialized = false;

public:
    ShapeMaskRenderer();
    void create(unsigned int width, unsigned int height);
    void setMask(const sf::Shape& shape);
    void drawMasked(const sf::Drawable& drawable);
    void display(sf::RenderTarget& target, sf::Vector2f position = {0, 0});
};
