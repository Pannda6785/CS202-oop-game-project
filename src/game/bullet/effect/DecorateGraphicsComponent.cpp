#include "DecorateGraphicsComponent.hpp"
#include "../Bullet.hpp"
#include <raylib.h>

DecorateGraphicsComponent::DecorateGraphicsComponent() {
    setLayer(Unit::Layer::Overlay);
}

void DecorateGraphicsComponent::addCircle(std::array<int, 4> color, float radius) {
    circles.push_back({color, radius});
}

void DecorateGraphicsComponent::addRing(std::array<int, 4> color, float radius, float thickness) {
    rings.push_back({color, radius, thickness});
}

void DecorateGraphicsComponent::render() const {
    if (!bullet) return;
    Unit::Vec2D pos = bullet->getPosition();
    float scale = bullet->getSize();

    for (const auto& c : circles) {
        Color drawColor = { (unsigned char)c.color[0], (unsigned char)c.color[1], (unsigned char)c.color[2], (unsigned char)c.color[3] };
        DrawCircleV({pos.x, pos.y}, c.radius * scale, drawColor);
    }
    for (const auto& r : rings) {
        Color drawColor = { (unsigned char)r.color[0], (unsigned char)r.color[1], (unsigned char)r.color[2], (unsigned char)r.color[3] };
        DrawRing({pos.x, pos.y}, std::max(0.0f, r.radius * scale - r.thickness / 2.0f), r.radius * scale + r.thickness / 2.0f, 0.0f, 360.0f, 128, drawColor);
    }
}
