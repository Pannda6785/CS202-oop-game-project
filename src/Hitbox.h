#ifndef HITBOX_H
#define HITBOX_H

#include "GameUnits.h"

class Hitbox {
public:
    virtual ~Hitbox() = default;

    virtual void setPosition(const Unit::Vec2D& pos) = 0;
    virtual Unit::Vec2D getPosition() const = 0;
    
    virtual void resize(float scale) = 0;

    virtual bool collidesWith(const Hitbox& other) const = 0;
    virtual bool collidesWithCircle(const class CircleHitbox& circle) const = 0;
    virtual bool collidesWithRectangle(const class RectangleHitbox& rect) const = 0;
};

#endif // HITBOX_H