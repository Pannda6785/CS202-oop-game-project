#include "CommonBulletGraphicsComponent.hpp"
#include <raylib.h>
#include <iostream>
#include <cmath>

#include "Bullet.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../../graphics/TextureManager.hpp"

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(float initialGradient)
    : initialGradient(std::max(0.1f, initialGradient)) {}

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(std::string texturePath, float texResize, float initialGradient, bool useVelocity,
    std::string startupTexturePath, float startUpTexResize)
    : texResize(texResize), startUpTexResize(startUpTexResize),
      initialGradient(std::max(0.1f, initialGradient)),
      useVelocity(useVelocity) {

    texture = TextureManager::instance().getTexture(texturePath);
    if (!startupTexturePath.empty()) {
        startupTexture = TextureManager::instance().getTexture(startupTexturePath);
    }
}

void CommonBulletGraphicsComponent::registerOwner(const Bullet* bullet) {
    BulletGraphicsComponent::registerOwner(bullet);
    this->bullet = bullet;
}

void CommonBulletGraphicsComponent::render() const {
    if (!bullet) {
        std::cerr << "Bullet not registered for CommonBulletGraphicsComponent rendering!" << std::endl;
        return;
    }

    Color tint = WHITE;
    tint.a = static_cast<unsigned char>(255 * gradient);
    Unit::Vec2D pos = bullet->getPosition();
    Unit::Vec2D velocity = bullet->getVelocity();

    float rotation = 0.0f;
    if (useVelocity) {
        if (velocity.x != 0.0f || velocity.y != 0.0f) {
            rotation = std::atan2(velocity.y, velocity.x) * RAD2DEG + 90.0f;
        }
    }

    if (texture) {
        const Texture* texToDraw = texture;
        float scale = texResize;

        if (startupTexture && !bullet->getDamagingHitbox()) {
            texToDraw = startupTexture;
            scale = startUpTexResize;
        }

        Rectangle source = { 0, 0, (float)texToDraw->width, (float)texToDraw->height };
        Rectangle dest = { pos.x, pos.y, source.width * scale, source.height * scale };
        Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };

        DrawTexturePro(*texToDraw, source, dest, origin, rotation, tint);
    } else {
        const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(bullet->getLifeHitbox());
        if (!hitbox) return;
        Vector2 pos2 = { pos.x, pos.y };
        float radius = hitbox->getRadius();
        DrawCircleV(pos2, radius, tint);
    }

    BulletGraphicsComponent::drawHitboxes();
}

void CommonBulletGraphicsComponent::update(float dt) {
    gradient += dt / initialGradient;
    if (gradient > 1.0f) {
        gradient = 1.0f;
    }
}
