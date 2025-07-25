#include "SunburstGraphicsComponent.hpp"
#include "Sunburst.hpp"

#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include "raylib.h"
#include <string>

SunburstGraphicsComponent::SunburstGraphicsComponent(const Sunburst* bullet)
    : BulletGraphicsComponent(bullet), bullet(bullet) {
    std::string path = "../assets/sprites/priestess/bullet/";
    inactiveTexture = TextureManager::instance().getTexture(path + "priest_bullets_6_p1_0001.png");
    activeTexture = TextureManager::instance().getTexture(path + "priest_bullets_3_p1_0002.png");
}

void SunburstGraphicsComponent::update(float dt) {
    rotationTimer += dt;
    gradient = std::min(1.0f, gradient + dt / INITIAL_GRADIENT);
    if (rotationTimer >= 1 / ROTATE_FPS) {
        int randStep = (rand() % 3 + 1) * 90;
        rotation += (float)randStep;
        if (rotation >= 360) rotation -= 360;
        flipped = rand() % 2 == 0;
        rotationTimer -= 1 / ROTATE_FPS;
    }
    if (bullet->isStartingUp()) {
        if (getLayer() != Unit::Layer::Underlay) setLayer(Unit::Layer::Underlay);
    } else {
        if (getLayer() != Unit::Layer::Bullet) setLayer(Unit::Layer::Bullet);
    }
}

void SunburstGraphicsComponent::render() const {
    if (!bullet) return;

    auto draw = [&](Texture currentTexture, bool underlay) -> void {
        Unit::Vec2D pos = bullet->getPosition();
        float bulletRadius = underlay ? bullet->getRingRadius() : bullet->getRadius();
        Color orange = {255, 60, 25, 255};
        orange.a = static_cast<unsigned char>(255 * gradient);

        // draw underlay tinted circle
        if (underlay) {
            DrawCircleV(Vector2{pos.x, pos.y}, bulletRadius, Fade(orange, 0.2f));
        }

        // draw texture
        constexpr float visibleRatio = 0.78f;
        float scale = (bulletRadius * 2.0f) / visibleRatio / currentTexture.width;
        Rectangle destRect = {
            pos.x, pos.y,
            currentTexture.width * scale,
            currentTexture.height * scale
        };
        Rectangle srcRect = { 0, 0, (float)currentTexture.width * (flipped ? -1.0f : 1.0f), (float)currentTexture.height };
        Vector2 origin = { currentTexture.width * scale / 2.0f, currentTexture.height * scale / 2.0f };
        DrawTexturePro(
            currentTexture,
            srcRect,
            destRect,
            origin,
            rotation,
            underlay ? orange : WHITE
        );
    };

    draw(*inactiveTexture, true);
    if (!bullet->isStartingUp()) draw(*activeTexture, false);

    BulletGraphicsComponent::drawHitboxes();
}
