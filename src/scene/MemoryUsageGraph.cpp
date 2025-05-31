#include "MemoryUsageGraph.h"
#include "OsStates.h"

void MemoryUsageGraph::MakeAMove(float UpdatedProgress)
{
    if (UpdatedProgress != 1)
        return;
    float mem = static_cast<float>(OsStates::GetProcessMemoryUsage() / (1024.0 * 1024.0));
    *this->value = mem;
    Update();
}

MemoryUsageGraph::MemoryUsageGraph()
{
    float *val = new float{0};
    this->SetValue(*val);
    this->SetCiclic(1);
    this->SetLabel("Mem in mb");
    this->SetDeltaTime(sf::seconds(1.f / 10.f));
}
