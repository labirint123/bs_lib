#include "Scene.h"

void Scene::add(sf::Text &o) {
    Texts.push_back(&o);
    drawables.push_back(&o);
}

void Scene::add(sf::Sprite &o) {
    Sprites.push_back(&o);
    drawables.push_back(&o);
}

void Scene::add(sf::RectangleShape &o) {
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

void Scene::add(sf::CircleShape &o) {
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

void Scene::add(sf::Shape *o) {
    Shapes.push_back(o);
    drawables.push_back(o);
}

void Scene::add(sf::VertexArray &o) {
    VertexArrays.push_back(&o);
    drawables.push_back(&o);
}

void Scene::add(Group &o) {
    Groups.push_back(&o);
    drawables.push_back(&o);
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    const sf::View prew(target.getView());
    target.setView(DefaultView);
    for (auto drawable : drawables) {
        target.draw(*drawable, states);
    }
    target.setView(prew);
}