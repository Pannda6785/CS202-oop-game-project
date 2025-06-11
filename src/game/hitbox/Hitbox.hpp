#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "../../Unit.hpp"

class CircleHitbox;
class RectangleHitbox;

class Hitbox {
public:
    virtual ~Hitbox() = default;

    virtual void setPosition(const Unit::Vec2D& pos) = 0;
    virtual Unit::Vec2D getPosition() const = 0;
    
    virtual void resize(float scale) = 0;

    virtual bool collidesWith(const Hitbox& other) const = 0;
    virtual bool collidesWithCircle(const CircleHitbox& circle) const = 0;
    virtual bool collidesWithRectangle(const RectangleHitbox& rect) const = 0;
};

#endif // HITBOX_HPP