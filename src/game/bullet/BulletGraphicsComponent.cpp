#include "BulletGraphicsComponent.hpp"
#include "Bullet.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../hitbox/RectangleHitbox.hpp"
#include "../devtool/DevTool.hpp"
#include <raylib.h>

BulletGraphicsComponent::BulletGraphicsComponent() {
    addTag("world_object");
    setLayer(Unit::Layer::Bullet);
}

void BulletGraphicsComponent::registerBullet(const Bullet* bullet) {
    this->bullet = bullet;
}

void BulletGraphicsComponent::render() const {
    drawHitboxes();
}

void BulletGraphicsComponent::drawHitboxes() const {
    if (!DevTool::isHitboxEnabled()) return;

    auto drawHitbox = [](const Hitbox* hitbox, Color baseColor) {
        Color color = baseColor;
        color.a = 130;
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

    drawHitbox(bullet->getLifeHitbox(), GREEN);
    drawHitbox(bullet->getDamagingHitbox(), RED);
    drawHitbox(bullet->getCleansingHitbox(), BLUE);
    for (const auto& [hitbox, major, id, duration] : bullet->getInvincibilityHitboxes()) {
        drawHitbox(hitbox, YELLOW);
    }
    for (const auto& [hitbox, modifier, id, duration, amount] : bullet->getModifierHitboxes()) {
        drawHitbox(hitbox, PURPLE);
    }
    for (const auto& [hitbox, lock, id, duration] : bullet->getLockHitboxes()) {
        drawHitbox(hitbox, PURPLE);
    }
}