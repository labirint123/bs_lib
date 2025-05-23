#include "ShapeMaskRenderer.h"

ShapeMaskRenderer::ShapeMaskRenderer() {}

void ShapeMaskRenderer::create(unsigned int width, unsigned int height) {
    size = {width, height};
    maskTexture.create(width, height);
    contentTexture.create(width, height);

    const std::string fragmentShader = R"(
        uniform sampler2D content;
        uniform sampler2D mask;
        void main() {
            vec4 c = texture2D(content, gl_TexCoord[0].xy);
            float m = texture2D(mask, gl_TexCoord[0].xy).a;
            gl_FragColor = vec4(c.rgb, c.a * m);
        }
    )";

    if (!maskShader.loadFromMemory(fragmentShader, sf::Shader::Fragment)) {
        throw std::runtime_error("Failed to load shader");
    }

    initialized = true;
}

void ShapeMaskRenderer::setMask(const sf::Shape& shape) {
    if (!initialized) return;
    maskTexture.clear(sf::Color::Transparent);
    maskTexture.draw(shape);
    maskTexture.display();
}

void ShapeMaskRenderer::drawMasked(const sf::Drawable& drawable) {
    if (!initialized) return;
    contentTexture.clear(sf::Color::Transparent);
    contentTexture.draw(drawable);
    contentTexture.display();
}

void ShapeMaskRenderer::display(sf::RenderTarget& target, sf::Vector2f position) {
    if (!initialized) return;

    sf::RectangleShape quad(sf::Vector2f(size.x, size.y));
    quad.setPosition(position);
    quad.setTexture(&contentTexture.getTexture());

    maskShader.setUniform("content", contentTexture.getTexture());
    maskShader.setUniform("mask", maskTexture.getTexture());

    target.draw(quad, &maskShader);
}
