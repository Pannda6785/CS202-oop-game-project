#ifndef RECTANGLE_HITBOX_HPP
#define RECTANGLE_HITBOX_HPP

#include "Hitbox.hpp"

class RectangleHitbox : public Hitbox {
public:
    RectangleHitbox(const Unit::Vec2D& center, float width, float height, float rotation = 0.0f);

    void setPosition(const Unit::Vec2D& pos) override;
    Unit::Vec2D getPosition() const override;

    void resize(float scale) override;
    
    bool collidesWith(const Hitbox& other) const override;
    bool collidesWithCircle(const CircleHitbox& circle) const override;
    bool collidesWithRectangle(const RectangleHitbox& other) const override;
    
    void setSize(float w, float h);
    float getWidth() const;
    float getHeight() const;

    void setRotation(float angleRadians);
    float getRotation() const;

private:
    Unit::Vec2D center;
    float width;
    float height;
    float rotation;
};

#endif // RECTANGLE_HITBOX_HPP
