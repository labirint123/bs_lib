#include "TickRateController.h"

void TickRateController::ControlTicks()
{
    if (IsFirstIteration)
        {
            clock.restart();
            IsFirstIteration = 1;
        }
    else
    {
        sf::Time t = clock.getElapsedTime();
        if (t.asSeconds() < this->deltatime.asSeconds())
        {
            sf::sleep(sf::seconds(this->deltatime.asSeconds() - t.asSeconds()));
        }        
        clock.restart();
    }
}

TickRateController::TickRateController()
{
}

TickRateController::~TickRateController()
{
}
