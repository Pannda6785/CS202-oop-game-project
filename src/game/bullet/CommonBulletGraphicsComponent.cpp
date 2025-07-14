#include "CommonBulletGraphicsComponent.hpp"
#include <raylib.h>

#include "Bullet.hpp"
#include "../hitbox/CircleHitbox.hpp"

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(const Bullet* bullet, float initialGradient)
    : bullet(bullet), initialGradient(std::max(0.1f, initialGradient)) {}

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(const Bullet* bullet, std::string texturePath, float initialGradient, std::string startupTexturePath)
    : bullet(bullet), texture(new Texture(LoadTexture(texturePath.c_str()))), initialGradient(std::max(0.1f, initialGradient)) {
    if (!startupTexturePath.empty()) {
        startupTexture = new Texture(LoadTexture(startupTexturePath.c_str()));
    }
}

CommonBulletGraphicsComponent::~CommonBulletGraphicsComponent() {
    if (texture) {
        UnloadTexture(*texture);
        delete texture;
    }
    if (startupTexture) {
        UnloadTexture(*startupTexture);
        delete startupTexture;
    }
}

void CommonBulletGraphicsComponent::render() const {
    Color tint = WHITE;
    tint.a = static_cast<unsigned char>(255 * gradient);
    if (texture) {
        Unit::Vec2D pos = bullet->getPosition();
        if (startupTexture && !bullet->getDamagingHitbox()) {
            DrawTextureEx(*startupTexture, { pos.x - startupTexture->width/2.0f, pos.y - startupTexture->height/2.0f }, 0.0f, 1.0f, tint);
        } else {
            DrawTextureEx(*texture, { pos.x - texture->width/2.0f, pos.y - texture->height/2.0f }, 0.0f, 1.0f, tint);
        }
    } else {
        const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(bullet->getLifeHitbox());
        if (!hitbox) return;
        Vector2 pos = { bullet->getPosition().x, bullet->getPosition().y };
        float radius = hitbox->getRadius();
        DrawCircleV(pos, radius, tint);
    }

}

void CommonBulletGraphicsComponent::update(float dt) {
    gradient += dt / initialGradient;
    if (gradient > 1.0f) {
        gradient = 1.0f;
    }
}