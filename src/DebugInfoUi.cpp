#include "DebugInfoUi.h"
#include "Utils.hpp"
void DebugInfoUi::Update()
{
    for (size_t i = 0; i < elms.size(); i++)
    {
        elms[i]->label.setString(elms[i]->param->name);
        elms[i]->ValueText.setString("value = " + std::to_string(elms[i]->param->value));
        elms[i]->label.setPosition(0, 0);
        elms[i]->ValueText.setPosition(0, GetSize(elms[i]->label).y + 10);
        elms[i]->size.y = elms[i]->ValueText.getPosition().y + GetSize(elms[i]->ValueText).y;
    }
    for (size_t i = 0; i < elms.size(); i++)
    {
        if (i == 0)
            continue;
        elms[i]->label.move(0,elms[i - 1]->size.y + 20);
        elms[i]->ValueText.move(0,elms[i - 1]->size.y + 20);
    }
}

int DebugInfoUi::AddParameter(parameter &par)
{
    Element *el = new Element;
    el->param = &par;
    this->elms.push_back(el);

    el->label.setFont(font);
    el->ValueText.setFont(font);

    el->label.setFillColor(sf::Color::White);
    el->ValueText.setFillColor(sf::Color::White);

    this->add(el->label);
    this->add(el->ValueText);


    Update();
    return elms.size() -1;
}

int DebugInfoUi::RemoveParameter(int index)
{
    return 0;
}

DebugInfoUi::DebugInfoUi()
{
}

void DebugInfoUi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (size_t i = 0; i < drawables.size(); i++)
    {
        target.draw(*drawables[i], states); // тут вылетает
    }
}

void DebugInfoUi::SetFont(sf::Font &font)
{
    this->font = font;
    for (size_t i = 0; i < elms.size(); i++)
    {
        elms[i]->label.setFont(font);
        elms[i]->ValueText.setFont(font);
    }
    
}
