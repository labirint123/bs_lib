#include "Item.h"

Item::Item(Signal<bool>& selected, std::string string)
{
    this->string = string;
    this->selected = selected;
}

std::string Item::getString()
{
    return string;
}

Signal<bool>& Item::getSelectedSignal()
{
    return selected;
}

unsigned int Item::getId()
{
    return id;
}
