#include "Group.h"
#include <algorithm>
#include "Log.h"
void Group::add(sf::Text& o)
{
    Texts.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::Sprite& o)
{
    Sprites.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::RectangleShape& o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::CircleShape& o)
{
    Shapes.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(sf::Shape* o)
{
    Shapes.push_back(o);
    drawables.push_back(o);
}

void Group::add(sf::VertexArray& o)
{
    VertexArrays.push_back(&o);
    drawables.push_back(&o);
}

void Group::add(Group &o)
{
    Groups.push_back(&o);
    drawables.push_back(&o);
}

sf::Vector2f Group::GetPosition() const { return Pos; }

void Group::SetPosition(sf::Vector2f pos)
{
    if (pos != Pos) onPositionChanged.emit(pos);
    Pos = pos;
}

void Group::move(sf::Vector2f offset)
{
    Pos += offset;
    if (offset != sf::Vector2f(0.f,0.f)) onPositionChanged.emit(Pos);
}

float Group::GetRotation() const { return Rotation; }

void Group::SetRotation(float rotation)
{
    if (rotation != Rotation) onRotationChanged.emit(rotation);
    Rotation = rotation;
}

void Group::rotate(float offset)
{
    Rotation += offset;
    if (offset != 0.f) onRotationChanged.emit(Rotation);
}

void Group::SetScale(sf::Vector2f scale)
{
    if (scale != Scale) onScaleChanged.emit(scale);
    Scale = scale;
}

void Group::scale(sf::Vector2f factor)
{
    Scale.x *= factor.x;
    Scale.y *= factor.y;
    if (factor != sf::Vector2f(1.f,1.f)) onScaleChanged.emit(Scale);
}

sf::Vector2f Group::GetScale() const { return Scale; }

void Group::SetOrigin(sf::Vector2f origin)
{
    if (origin != Origin) onOriginChanged.emit(origin);
    Origin = origin;
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

void Group::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (auto d : drawables)
        target.draw(*d, states);
}

sf::FloatRect Group::getBounds() const
{
    bool has = false;
    sf::FloatRect bounds;

    auto merge = [&](const sf::FloatRect& r) {
        if (!has) {
            bounds = r;
            has = true;
        } else {
            float l  = std::min(bounds.left,             r.left);
            float t  = std::min(bounds.top,              r.top);
            float rr = std::max(bounds.left + bounds.width,  r.left + r.width);
            float bb = std::max(bounds.top  + bounds.height, r.top  + r.height);
            bounds.left   = l;
            bounds.top    = t;
            bounds.width  = rr - l;
            bounds.height = bb - t;
        }
    };

    // Трансформация этой группы
    sf::Transform tr = getTransform();

    // Texts
    for (auto txt : Texts) {
        auto lb = txt->getLocalBounds();
        sf::Vector2f pts[4] = {
            tr.transformPoint(lb.left,             lb.top),
            tr.transformPoint(lb.left + lb.width,  lb.top),
            tr.transformPoint(lb.left,             lb.top + lb.height),
            tr.transformPoint(lb.left + lb.width,  lb.top + lb.height)
        };
        sf::FloatRect r{ pts[0].x, pts[0].y, 0.f, 0.f };
        for (int i = 1; i < 4; ++i) {
            r.left   = std::min(r.left,   pts[i].x);
            r.top    = std::min(r.top,    pts[i].y);
            r.width  = std::max(r.width,  pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    // Sprites
    for (auto sp : Sprites) {
        auto lb = sp->getLocalBounds();
        sf::Transform t2 = tr * sp->getTransform();
        sf::Vector2f pts[4] = {
            t2.transformPoint(lb.left,             lb.top),
            t2.transformPoint(lb.left + lb.width,  lb.top),
            t2.transformPoint(lb.left,             lb.top + lb.height),
            t2.transformPoint(lb.left + lb.width,  lb.top + lb.height)
        };
        sf::FloatRect r{ pts[0].x, pts[0].y, 0.f, 0.f };
        for (int i = 1; i < 4; ++i) {
            r.left   = std::min(r.left,   pts[i].x);
            r.top    = std::min(r.top,    pts[i].y);
            r.width  = std::max(r.width,  pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    // Shapes (RectangleShape, CircleShape и др.)
    for (auto sh : Shapes) {
        auto lb = sh->getLocalBounds();
        sf::Transform t2 = tr * sh->getTransform();
        sf::Vector2f pts[4] = {
            t2.transformPoint(lb.left,             lb.top),
            t2.transformPoint(lb.left + lb.width,  lb.top),
            t2.transformPoint(lb.left,             lb.top + lb.height),
            t2.transformPoint(lb.left + lb.width,  lb.top + lb.height)
        };
        sf::FloatRect r{ pts[0].x, pts[0].y, 0.f, 0.f };
        for (int i = 1; i < 4; ++i) {
            r.left   = std::min(r.left,   pts[i].x);
            r.top    = std::min(r.top,    pts[i].y);
            r.width  = std::max(r.width,  pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    // Вложенные группы — берём их свои bounds и применяем только трансформ этой группы
    for (auto grp : Groups) {
        sf::FloatRect lb = grp->getBounds();  // уже содержит преобразования grp
        sf::Vector2f pts[4] = {
            tr.transformPoint(lb.left,             lb.top),
            tr.transformPoint(lb.left + lb.width,  lb.top),
            tr.transformPoint(lb.left,             lb.top + lb.height),
            tr.transformPoint(lb.left + lb.width,  lb.top + lb.height)
        };
        sf::FloatRect r{ pts[0].x, pts[0].y, 0.f, 0.f };
        for (int i = 1; i < 4; ++i) {
            r.left   = std::min(r.left,   pts[i].x);
            r.top    = std::min(r.top,    pts[i].y);
            r.width  = std::max(r.width,  pts[i].x - r.left);
            r.height = std::max(r.height, pts[i].y - r.top);
        }
        merge(r);
    }

    // VertexArrays
    for (auto va : VertexArrays) {
        bool first = true;
        sf::FloatRect r;
        for (std::size_t i = 0; i < va->getVertexCount(); ++i) {
            auto p = tr.transformPoint((*va)[i].position);
            if (first) {
                r.left = p.x; r.top = p.y; r.width = r.height = 0.f;
                first = false;
            } else {
                r.left   = std::min(r.left,   p.x);
                r.top    = std::min(r.top,    p.y);
                r.width  = std::max(r.width,  p.x - r.left);
                r.height = std::max(r.height, p.y - r.top);
            }
        }
        if (!first)
            merge(r);
    }

    return has ? bounds : sf::FloatRect();
}
