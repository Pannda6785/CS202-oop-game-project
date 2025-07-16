#include "BulletGraphicsComponent.hpp"
#include "Bullet.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../hitbox/RectangleHitbox.hpp"
#include <raylib.h>

BulletGraphicsComponent::BulletGraphicsComponent(bool drawHitbox) : drawHitbox(drawHitbox) {
    setLayer(Unit::Layer::Bullet);
}

void BulletGraphicsComponent::registerOwner(const Bullet* bullet) {
    this->owner = bullet;
}

void BulletGraphicsComponent::drawHitboxes() const {
    if (!drawHitbox || !owner) return;

    auto drawHitbox = [](const Hitbox* hitbox, Color baseColor) {
        Color color = baseColor;
        color.a = 170;
        if (const auto* circle = dynamic_cast<const CircleHitbox*>(hitbox)) {
            Vector2 pos = { circle->getPosition().x, circle->getPosition().y };
            DrawCircleV(pos, circle->getRadius(), color);
        } else if (const auto* rect = dynamic_cast<const RectangleHitbox*>(hitbox)) {
            float w = rect->getWidth();
            float h = rect->getHeight();
            Vector2 pos = { rect->getPosition().x, rect->getPosition().y };
            float rot = rect->getRotation() * RAD2DEG;
            DrawRectanglePro({ pos.x, pos.y, w, h }, { w / 2.0f, h / 2.0f }, rot, color);
        }
    };

    drawHitbox(owner->getLifeHitbox(), GREEN);
    drawHitbox(owner->getDamagingHitbox(), RED);
    drawHitbox(owner->getCleansingHitbox(), BLUE);
    for (const auto& [hitbox, id, duration] : owner->getInvincibilityHitboxes()) {
        drawHitbox(hitbox, YELLOW);
    }
}