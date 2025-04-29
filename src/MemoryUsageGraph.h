#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "GraphWidget.h"

class MemoryUsageGraph : public GraphWidget, public Animation
{
protected:
    void MakeAMove(float UpdatedProgress) override;
    Animation *Clone() const override { return new MemoryUsageGraph(*this); }
public:
    MemoryUsageGraph();
};
