#include "SizeAnim.h"

void SizeAnim::SetObjSize(sf::Vector2f size)
{
    if (RectShapeObj != nullptr)
    {
        RectShapeObj->setSize(size);
    }
    else if (CircShapeObj != nullptr)
    {
        CircShapeObj->setRadius(size.x);
    }
    else if (SpriteObj != nullptr)
    {
        SpriteObj->setScale(size.x / SpriteObj->getTextureRect().getSize().x, size.y / SpriteObj->getTextureRect().getSize().y);
    }
}

sf::Vector2f SizeAnim::GetObjSize()
{
    sf::Vector2f ret;
    if (RectShapeObj != nullptr)
    {
        ret = RectShapeObj->getSize();
    }
    else if (CircShapeObj != nullptr)
    {
        ret = {CircShapeObj->getRadius(), 0};
    }
    else if (SpriteObj != nullptr)
    {
        ret = {SpriteObj->getTextureRect().getSize().x, SpriteObj->getTextureRect().getSize().y};
    }
    return ret;
}

void SizeAnim::ToDoAtStart()
{
    if (RectShapeObj != nullptr)
    {
        this->StartSize = RectShapeObj->getSize();
    }
    else if (CircShapeObj != nullptr)
    {
        this->StartSize = {CircShapeObj->getRadius(), 0};
    }
    else if (SpriteObj != nullptr)
    {
        this->StartSize = {SpriteObj->getTextureRect().getSize().x, SpriteObj->getTextureRect().getSize().y};
    }
    LastProgress = 0;
}

void SizeAnim::MakeAMove(float UpdatedProgress)
{
    float d = UpdatedProgress - LastProgress;
    sf::Vector2f dv = FinalSize - StartSize;
    SetObjSize(GetObjSize() + dv * d);
    LastProgress = UpdatedProgress;
}

void SizeAnim::SetObj(sf::Sprite &obj)
{
    SpriteObj = &obj;
    CircShapeObj = nullptr;
    RectShapeObj = nullptr;
}

void SizeAnim::SetObj(sf::RectangleShape &obj)
{
    RectShapeObj = &obj;
    SpriteObj = nullptr;
    CircShapeObj = nullptr;
}

void SizeAnim::SetObj(sf::CircleShape &obj)
{
    CircShapeObj = &obj;
    SpriteObj = nullptr;
    RectShapeObj = nullptr;
}

void SizeAnim::SetSize(sf::Vector2f size)
{
    this->FinalSize = size;
}
