#include "CircleHitbox.hpp"
#include "RectangleHitbox.hpp"
#include <algorithm>

CircleHitbox::CircleHitbox(const Unit::Vec2D& center, float radius)
    : center(center), radius(radius) {}

void CircleHitbox::setPosition(const Unit::Vec2D& pos) {
    center = pos;
}

Unit::Vec2D CircleHitbox::getPosition() const {
    return center;
}

void CircleHitbox::resize(float scale) {
    radius *= scale;
}

void CircleHitbox::setRadius(float r) {
    radius = r;
}

float CircleHitbox::getRadius() const {
    return radius;
}

bool CircleHitbox::collidesWith(const Hitbox& other) const {
    return other.collidesWithCircle(*this);
}

bool CircleHitbox::collidesWithCircle(const CircleHitbox& other) const {
    float dx = center.x - other.center.x;
    float dy = center.y - other.center.y;
    float distSq = dx * dx + dy * dy;
    float combinedRadius = radius + other.radius;
    return distSq <= combinedRadius * combinedRadius;
}

bool CircleHitbox::collidesWithRectangle(const RectangleHitbox& rect) const {
    // Rotate circle center into rect's local space
    float cosTheta = std::cos(-rect.getRotation());
    float sinTheta = std::sin(-rect.getRotation());

    Unit::Vec2D rel = center - rect.getPosition();
    Unit::Vec2D local = {
        rel.x * cosTheta - rel.y * sinTheta,
        rel.x * sinTheta + rel.y * cosTheta
    };

    float halfW = rect.getWidth() / 2.0f;
    float halfH = rect.getHeight() / 2.0f;

    float clampedX = std::clamp(local.x, -halfW, halfW);
    float clampedY = std::clamp(local.y, -halfH, halfH);

    float dx = local.x - clampedX;
    float dy = local.y - clampedY;
    return (dx * dx + dy * dy) <= (radius * radius);
}
