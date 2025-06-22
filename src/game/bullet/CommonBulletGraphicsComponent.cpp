#include "CommonBulletGraphicsComponent.hpp"
#include <raylib.h>

#include "CommonBullet.hpp"
#include "../hitbox/CircleHitbox.hpp"

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(const CommonBullet* bullet)
    : bullet(bullet), texture(nullptr), useTexture(false) {}

CommonBulletGraphicsComponent::CommonBulletGraphicsComponent(const CommonBullet* bullet, const std::string& texturePath)
    : bullet(bullet), texture(new Texture2D(LoadTexture(texturePath.c_str()))), useTexture(true) {}

CommonBulletGraphicsComponent::~CommonBulletGraphicsComponent() {
    if (texture) {
        UnloadTexture(*texture);
        delete texture;
    }
}

void CommonBulletGraphicsComponent::render() const {
    const CircleHitbox* hitbox = dynamic_cast<const CircleHitbox*>(bullet->getLifeHitbox());
    if (!hitbox) return;

    Vector2 pos = { bullet->getPosition().x, bullet->getPosition().y };
    float radius = hitbox->getRadius();

    if (useTexture && texture) {
        Color tint = WHITE;
        tint.a = bullet->getDamagingHitbox() ? 255 : 128; // Semi-transparent if not started up
        DrawTextureEx(*texture, { pos.x - texture->width/2.0f, pos.y - texture->height/2.0f }, 0.0f, 1.0f, tint);
    } else {
        Color tint = RED;
        tint.a = bullet->getDamagingHitbox() ? 255 : 128; // Semi-transparent if not started up
        DrawCircleV(pos, radius, tint);
    }
}