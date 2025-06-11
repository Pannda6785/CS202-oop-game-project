#ifndef CIRCLE_HITBOX_HPP
#define CIRCLE_HITBOX_HPP

#include "Hitbox.hpp"

class CircleHitbox : public Hitbox {
public:
    CircleHitbox(const Unit::Vec2D& center, float radius);

    void setPosition(const Unit::Vec2D& pos) override;
    Unit::Vec2D getPosition() const override;

    void resize(float scale) override;
    
    bool collidesWith(const Hitbox& other) const override;
    bool collidesWithCircle(const CircleHitbox& circle) const override;
    bool collidesWithRectangle(const RectangleHitbox& rect) const override;

    void setRadius(float r);
    float getRadius() const;

private:
    Unit::Vec2D center;
    float radius;
};

#endif // CIRCLE_HITBOX_HPP
