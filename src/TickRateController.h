#pragma once
#include <SFML/System.hpp>

class TickRateController
{
private:
    sf::Time deltatime;
    bool IsFirstIteration = 0;
    sf::Clock clock;
public:
    void setDeltatime(sf::Time deltaTime){this->deltatime = deltaTime;}
    void setTimesPerSec(float timesPerSec){this->setDeltatime(sf::seconds(sf::seconds(1).asSeconds()/timesPerSec));}
    void ControlTicks();
    TickRateController(/* args */);
    ~TickRateController();
};
