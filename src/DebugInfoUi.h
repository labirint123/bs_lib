#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Group.h"

struct parameter
{
    std::string name = "???";
    float value = 0;
    sf::Color color;
    parameter(){}
    parameter(std::string name,float value,sf::Color color){
        this->color = color;
        this->name = name;
        this->value = value;
    }
};

class DebugInfoUi : public Group
{
private:
    struct Element
    {
        parameter* param;
        sf::Text label;
        sf::Text ValueText;
        sf::Vector2f size;
        std::vector<sf::RectangleShape> graphobjs;
        sf::RectangleShape MainBg;
        sf::RectangleShape GraphBg;
    };    
   sf::Font font;
   sf::Time logTime = sf::seconds(1);
public:
    std::vector<Element*> elms;
    int AddParameter(parameter &par);
    int RemoveParameter(int index);
    DebugInfoUi();
    void Update();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void SetFont(sf::Font &font);
 
    
};
