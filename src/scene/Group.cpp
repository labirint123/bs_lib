#include "Group.h"
#include <algorithm>
#include "Log.h"

#include "Group.h"
#include <algorithm>
#include "Log.h"

void Group::add(sf::Text &o)
{
    Texts.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(sf::Sprite &o)
{
    Sprites.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(sf::RectangleShape &o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(sf::CircleShape &o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(sf::Shape *o)
{
    Shapes.push_back(o);
    drawables.push_back(o);
    onBoundsChanged.emit();
}

void Group::add(sf::VertexArray &o)
{
    VertexArrays.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(Group &o)
{
    Groups.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

void Group::add(RoundedRectangleShape &o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
    onBoundsChanged.emit();
}

sf::Vector2f Group::getPosition() const { return Pos; }

void Group::setPosition(sf::Vector2f pos)
{
    if (pos != Pos)
    {
        Pos = pos;
        onPositionChanged.emit(pos);
        onBoundsChanged.emit();
    }
}

void Group::move(sf::Vector2f offset)
{
    if (offset != sf::Vector2f(0.f, 0.f))
    {
        Pos += offset;
        onPositionChanged.emit(Pos);
        onBoundsChanged.emit();
    }
}

float Group::getRotation() const { return Rotation; }

void Group::setRotation(float rotation)
{
    if (rotation != Rotation)
    {
        Rotation = rotation;
        onRotationChanged.emit(rotation);
        onBoundsChanged.emit();
    }
}

void Group::rotate(float offset)
{
    if (offset != 0.f)
    {
        Rotation += offset;
        onRotationChanged.emit(Rotation);
        onBoundsChanged.emit();
    }
}

void Group::setScale(sf::Vector2f scale)
{
    if (scale != Scale)
    {
        Scale = scale;
        onScaleChanged.emit(scale);
        onBoundsChanged.emit();
    }
}

void Group::scale(sf::Vector2f factor)
{

    if (factor != sf::Vector2f(1.f, 1.f))
    {
        Scale.x *= factor.x;
        Scale.y *= factor.y;
        onScaleChanged.emit(Scale);
        onBoundsChanged.emit();
    }
}

sf::Vector2f Group::getScale() const { return Scale; }

void Group::SetOrigin(sf::Vector2f origin)
{
    if (origin != Origin)
    {
        Origin = origin;
        onOriginChanged.emit(origin);
        onBoundsChanged.emit();
    }
}

sf::Vector2f Group::GetOrigin() const { return Origin; }

sf::Transform Group::getTransform() const
{
    sf::Transform t;
    t.translate(Pos);
    t.rotate(Rotation);
    t.scale(Scale);
    t.translate(-Origin);
    return t;
}

void Group::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (auto d : drawables)
        target.draw(*d, states);
}

sf::FloatRect Group::getBounds() const
{
    bool has = false;
    sf::FloatRect bounds;

    auto merge = [&](const sf::FloatRect &r)
    {
        if (!has)
        {
            bounds = r;
            has = true;
        }
        else
        {
            float l = std::min(bounds.left, r.left);
            float t = std::min(bounds.top, r.top);
            float rr = std::max(bounds.left + bounds.width, r.left + r.width);
            float bb = std::max(bounds.top + bounds.height, r.top + r.height);
            bounds.left = l;
            bounds.top = t;
            bounds.width = rr - l;
            bounds.height = bb - t;
        }
    };

    sf::Transform tr = getTransform();

    for (auto txt : Texts)
    {
        auto lb = txt->getLocalBounds();
        sf::Vector2f pts[4] = {
            tr.transformPoint(lb.left, lb.top),
            tr.transformPoint(lb.left + lb.width, lb.top),
            tr.transformPoint(lb.left, lb.top + lb.height),
            tr.transformPoint(lb.left + lb.width, lb.top + lb.height)};
        sf::FloatRect r{pts[0].x, pts[0].y, 0.f, 0.f};
        for (int i = 1; i < 4; ++i)
        {
            r.left = std::min(r.left, pts[i].x);
            r.top = std::min(r.top, pts[i].y);
            r.width = std::max(r.width, pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    for (auto sp : Sprites)
    {
        auto lb = sp->getLocalBounds();
        sf::Transform t2 = tr * sp->getTransform();
        sf::Vector2f pts[4] = {
            t2.transformPoint(lb.left, // VertexArrays
                              lb.top),
            t2.transformPoint(lb.left + lb.width, lb.top),
            t2.transformPoint(lb.left, lb.top + lb.height),
            t2.transformPoint(lb.left + lb.width, lb.top + lb.height)};
        sf::FloatRect r{pts[0].x, pts[0].y, 0.f, 0.f};
        for (int i = 1; i < 4; ++i)
        {
            r.left = std::min(r.left, pts[i].x);
            r.top = std::min(r.top, pts[i].y);
            r.width = std::max(r.width, pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    for (auto sh : Shapes)
    {
        auto lb = sh->getLocalBounds();
        sf::Transform t2 = tr * sh->getTransform();
        sf::Vector2f pts[4] = {
            t2.transformPoint(lb.left, lb.top),
            t2.transformPoint(lb.left + lb.width, lb.top),
            t2.transformPoint(lb.left, lb.top + lb.height),
            t2.transformPoint(lb.left + lb.width, lb.top + lb.height)};
        sf::FloatRect r{pts[0].x, pts[0].y, 0.f, 0.f};
        for (int i = 1; i < 4; ++i)
        {
            r.left = std::min(r.left, pts[i].x);
            r.top = std::min(r.top, pts[i].y);
            r.width = std::max(r.width, pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    for (auto grp : Groups)
    {
        sf::FloatRect lb = grp->getBounds(); // уже содержит преобразования grp
        sf::Vector2f pts[4] = {
            tr.transformPoint(lb.left, lb.top),
            tr.transformPoint(lb.left + lb.width, lb.top),
            tr.transformPoint(lb.left, lb.top + lb.height),
            tr.transformPoint(lb.left + lb.width, lb.top + lb.height)};
        sf::FloatRect r{pts[0].x, pts[0].y, 0.f, 0.f};
        for (int i = 1; i < 4; ++i)
        {
            r.left = std::min(r.left, pts[i].x);
            r.top = std::min(r.top, pts[i].y);
            r.width = std::max(r.width, pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    for (auto va : VertexArrays)
    {
        bool first = true;
        sf::FloatRect r;
        for (std::size_t i = 0; i < va->getVertexCount(); ++i)
        {
            auto p = tr.transformPoint((*va)[i].position);
            if (first)
            {
                r.left = p.x;
                r.top = p.y;
                r.width = r.height = 0.f;
                first = false;
            }
            else
            {
                r.left = std::min(r.left, p.x);
                r.top = std::min(r.top, p.y);
                r.width = std::max(r.width, p.x - r.left);
                r.height = std::max(r.height, p.y - r.top);
            }
        }
        if (!first)
            merge(r);
    }

    return has ? bounds : sf::FloatRect();
}
