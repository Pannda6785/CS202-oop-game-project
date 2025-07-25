#include "NoviDispelGraphicsComponent.hpp"

#include "../../../bullet/Bullet.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <raylib.h>

NoviDispelGraphicsComponent::NoviDispelGraphicsComponent(const Bullet* bullet) : BulletGraphicsComponent(bullet) {
    setLayer(Unit::Layer::Underlay);
    std::string path = "../assets/sprites/priestess/bullet/dispel.png";
    texture = TextureManager::instance().getTexture(path);
}

void NoviDispelGraphicsComponent::render() const {
    if (!bullet || !texture) return;

    // Draw the feathery zone
    Unit::Vec2D pos = bullet->getPosition();

    float radius = dynamic_cast<const CircleHitbox*>(std::get<0>(bullet->getInvincibilityHitboxes()[0]))->getRadius();
    constexpr float visibleRatio = 0.93f; 

    float scale = (radius * 2.0f) / visibleRatio / texture->width;
    Rectangle destRect = { pos.x, pos.y, texture->width * scale, texture->height * scale };
    Rectangle srcRect = { 0, 0, (float)texture->width, (float)texture->height };
    Vector2 origin = { texture->width * scale / 2.0f, texture->height * scale / 2.0f };

    DrawTexturePro(*texture, srcRect, destRect, origin, rotation, WHITE);

      // Render the ripple
    if (rippleActive) {
        float alpha = 1.0f - (rippleTimer / RIPPLE_DURATION); // fade out
        for (int i = 0; i < RIPPLE_COUNT; ++i) {
            float t = (float)i / RIPPLE_COUNT;
            float progress = (rippleTimer / RIPPLE_DURATION) + t;
            if (progress > 1.0f) continue;
            float rippleRadius = radius * 0.97 + (progress * RIPPLE_SPREAD);
            Color ringColor = Fade(WHITE, alpha * (1.0f - t));
            DrawRing(
                { pos.x, pos.y },
                rippleRadius - RIPPLE_WIDTH,
                rippleRadius,
                0.0f, 360.0f, 64,
                ringColor
            );
        }
    }

    BulletGraphicsComponent::drawHitboxes();
}

void NoviDispelGraphicsComponent::update(float dt) {
    rotationTimer += dt;
    if (rotationTimer >= 1 / ROTATE_FPS) {
        int randStep = 90;
        rotation += (float)randStep;
        if (rotation >= 360) rotation -= 360;
        rotationTimer -= 1 / ROTATE_FPS;
    }
    if (rippleActive) {
        rippleTimer += dt;
        if (rippleTimer >= RIPPLE_DURATION) {
            rippleActive = false;
        }
    }
}