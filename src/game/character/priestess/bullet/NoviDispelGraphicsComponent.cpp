#include "NoviDispelGraphicsComponent.hpp"
#include "NoviDispel.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

#include <raylib.h>

NoviDispelGraphicsComponent::NoviDispelGraphicsComponent(const NoviDispel* bullet)
    : bullet(bullet)
{
    std::string path = "../assets/sprites/priestess/bullet/dispel.png";
    texture = new Texture(LoadTexture(path.c_str()));
    BulletGraphicsComponent::registerOwner(bullet);
}

NoviDispelGraphicsComponent::~NoviDispelGraphicsComponent() {
    if (texture) {
        UnloadTexture(*texture);
        delete texture;
    }
}

void NoviDispelGraphicsComponent::render() const {
    if (!bullet || !texture) return;

    Unit::Vec2D pos = bullet->getPosition();

    float radius = dynamic_cast<const CircleHitbox*>(std::get<0>(bullet->getInvincibilityHitboxes()[0]))->getRadius();
    constexpr float visibleRatio = 0.93f; 

    float scale = (radius * 2.0f) / visibleRatio / texture->width;
    Rectangle destRect = { pos.x, pos.y, texture->width * scale, texture->height * scale };
    Rectangle srcRect = { 0, 0, (float)texture->width, (float)texture->height };
    Vector2 origin = { texture->width * scale / 2.0f, texture->height * scale / 2.0f };

    DrawTexturePro(*texture, srcRect, destRect, origin, rotation, WHITE);

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
}