#include "FrameTimeGraph.h"
#include <sstream>
#include <iomanip>

FrameTimeGraph::FrameTimeGraph()
{
    float *val = new float{0};
    this->SetValue(*val);
    this->SetLabel("FrameTime");
}

void FrameTimeGraph::UpdateFrame()
{
    float ms = timer.restart().asSeconds() * 1000;
    *this->value = ms;
    this->Update();

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << ms; 
    std::string f = oss.str();

    if (auto pos = f.find('.'); pos != std::string::npos)
    {
        f.erase(f.find_last_not_of('0') + 1);
        if (f.back() == '.')
            f.pop_back();
    }

    this->ValText.setString(f);
}
