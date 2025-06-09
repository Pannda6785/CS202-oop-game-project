#include "RectangleHitbox.h"
#include "CircleHitbox.h"
#include <cmath>
#include <array>

RectangleHitbox::RectangleHitbox(const Unit::Vec2D& center, float width, float height, float rotation)
    : center(center), width(width), height(height), rotation(rotation) {}

void RectangleHitbox::setPosition(const Unit::Vec2D& pos) {
    center = pos;
}

Unit::Vec2D RectangleHitbox::getPosition() const {
    return center;
}

void RectangleHitbox::resize(float scale) {
    width *= scale;
    height *= scale;
}

void RectangleHitbox::setSize(float w, float h) {
    width = w;
    height = h;
}

float RectangleHitbox::getWidth() const {
    return width;
}

float RectangleHitbox::getHeight() const {
    return height;
}

void RectangleHitbox::setRotation(float angleRadians) {
    rotation = angleRadians;
}

float RectangleHitbox::getRotation() const {
    return rotation;
}

bool RectangleHitbox::collidesWith(const Hitbox& other) const {
    return other.collidesWithRectangle(*this);
}

bool RectangleHitbox::collidesWithCircle(const CircleHitbox& circle) const {
    return circle.collidesWithRectangle(*this); // Delegate to Circle for consistent logic
}

bool RectangleHitbox::collidesWithRectangle(const RectangleHitbox& other) const {
    // Helper function to rotate a point around center
    auto rotate = [](const Unit::Vec2D& point, float angle) {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return Unit::Vec2D{
            point.x * cosA - point.y * sinA,
            point.x * sinA + point.y * cosA
        };
    };

    // Get corners of rectangle
    auto getCorners = [&](const RectangleHitbox& rect) -> std::array<Unit::Vec2D, 4> {
        float w = rect.width / 2.0f;
        float h = rect.height / 2.0f;

        std::array<Unit::Vec2D, 4> localCorners = {{
            {-w, -h}, {w, -h}, {w, h}, {-w, h}
        }};

        std::array<Unit::Vec2D, 4> worldCorners;
        for (int i = 0; i < 4; ++i) {
            Unit::Vec2D rotated = rotate(localCorners[i], rect.rotation);
            worldCorners[i] = { rotated.x + rect.center.x, rotated.y + rect.center.y };
        }
        return worldCorners;
    };

    // Get the corners of both rectangles
    auto cornersA = getCorners(*this);
    auto cornersB = getCorners(other);

    // Function to compute dot product
    auto dot = [](const Unit::Vec2D& a, const Unit::Vec2D& b) -> float {
        return a.x * b.x + a.y * b.y;
    };

    // Function to get normalized perpendicular axis
    auto getAxes = [](const std::array<Unit::Vec2D, 4>& corners) -> std::array<Unit::Vec2D, 2> {
        std::array<Unit::Vec2D, 2> axes;
        for (int i = 0; i < 2; ++i) {
            Unit::Vec2D edge = {
                corners[i + 1].x - corners[i].x,
                corners[i + 1].y - corners[i].y
            };
            // Perpendicular
            Unit::Vec2D axis = { -edge.y, edge.x };
            float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
            if (length != 0) {
                axis.x /= length;
                axis.y /= length;
            }
            axes[i] = axis;
        }
        return axes;
    };

    // Get all axes to test (2 from each rectangle)
    std::array<Unit::Vec2D, 4> axes;
    auto axesA = getAxes(cornersA);
    auto axesB = getAxes(cornersB);
    axes[0] = axesA[0];
    axes[1] = axesA[1];
    axes[2] = axesB[0];
    axes[3] = axesB[1];

    // SAT test on all axes
    for (const auto& axis : axes) {
        float minA = dot(cornersA[0], axis), maxA = minA;
        for (int i = 1; i < 4; ++i) {
            float projection = dot(cornersA[i], axis);
            if (projection < minA) minA = projection;
            if (projection > maxA) maxA = projection;
        }

        float minB = dot(cornersB[0], axis), maxB = minB;
        for (int i = 1; i < 4; ++i) {
            float projection = dot(cornersB[i], axis);
            if (projection < minB) minB = projection;
            if (projection > maxB) maxB = projection;
        }

        // Check for separating axis
        if (maxA < minB || maxB < minA) {
            return false; // No collision
        }
    }

    return true; // Overlaps on all axes => collision
}
