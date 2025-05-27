#pragma once
#include "string"
#include "signal.h"

class Item
{
public:
    Item(Signal<bool> &selected, std::string string);
    std::string getString();
    Signal<bool>& getSelectedSignal();
    unsigned int getId();
private:
    Signal<bool> selected;
    std::string string;
    unsigned int id;
};
