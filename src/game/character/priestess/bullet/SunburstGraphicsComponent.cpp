#include "SunburstGraphicsComponent.hpp"
#include "Sunburst.hpp"
#include "raylib.h"

#include <string>

#include "../../../hitbox/CircleHitbox.hpp"

SunburstGraphicsComponent::SunburstGraphicsComponent(const Sunburst* bullet)
    : bullet(bullet) {
    std::string path = "../assets/sprites/priestess/bullet/";
    inactiveTexture = new Texture(LoadTexture((path + "priest_bullets_6_p1_0001.png").c_str()));
    activeTexture = new Texture(LoadTexture((path + "priest_bullets_3_p1_0002.png").c_str()));
}

SunburstGraphicsComponent::~SunburstGraphicsComponent() {
    UnloadTexture(*inactiveTexture);
    UnloadTexture(*activeTexture);
    delete inactiveTexture;
    delete activeTexture;
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
}

void SunburstGraphicsComponent::render() const {
    if (!bullet) return;

    Texture currentTexture = *(bullet->isStartingUp() ? inactiveTexture : activeTexture);

    Unit::Vec2D pos = bullet->getPosition();
    float bulletRadius = bullet->getRadius();

    constexpr float visibleRatio = 0.78f; 
    float scale = (bulletRadius * 2.0f) / visibleRatio / currentTexture.width;

    Rectangle destRect = {
        pos.x, pos.y,
        currentTexture.width * scale,
        currentTexture.height * scale
    };
    
    Rectangle srcRect = { 0, 0, (float)currentTexture.width * (flipped ? -1.0f : 1.0f), (float)currentTexture.height };

    Vector2 origin = { currentTexture.width * scale / 2.0f, currentTexture.height * scale / 2.0f };

    Color color = {255, 60, 25, 255};
    Color tint = color;
    tint.a = static_cast<unsigned char>(255 * gradient);

    DrawTexturePro(
        currentTexture,
        srcRect,
        destRect,
        origin,
        rotation,
        (bullet->isStartingUp() ? tint : WHITE)
    );

    float thickness = 5;
    tint.a = std::min((int)tint.a, 150);
    DrawRing({pos.x, pos.y}, bullet->getRingRadius() - thickness / 2, bullet->getRingRadius() + thickness / 2, 0, 360, 64, tint);
}
