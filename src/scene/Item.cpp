#include "Item.h"

Item::Item(std::string string)
{
    this->string = string;
}

Item::Item()
{

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
