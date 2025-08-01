#include "DepthWideHandler.hpp"
#include "../../../player/Player.hpp"
#include "../DepthGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

#include <cmath>

DepthWideHandler::DepthWideHandler(DepthGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void DepthWideHandler::tap(bool isFocusing) {
    graphics->useWide();

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
}

void DepthWideHandler::spawnBullet() {
    constexpr float MY_PI = 3.14159265358979323846f;

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D target = player->getTargetPosition();
    Unit::Vec2D aimDir = (target - pos).normalized();

    constexpr float ANGLE_STEP = 360.0f / NUM_BULLETS;
    float baseAngle = std::atan2(aimDir.y, aimDir.x) * 180.0f / static_cast<float>(MY_PI) + ANGLE_STEP / 2;

    const Texture* bulletTexture = TextureManager::instance().getTexture("../assets/sprites/depth/bullet/hydra_bullets_0_p1_0001.png");
    constexpr float visibleRatio = 3.5f / 6.0f;
    constexpr float textureWidth = 512;
    constexpr float resize = (RADIUS * 2) / (textureWidth * visibleRatio);

    for (int wave = 0; wave < 2; ++wave) {
        float speed = (wave == 0) ? SPEED_IN : SPEED_OUT;

        for (int i = 0; i < NUM_BULLETS; ++i) {
            float angleDeg = baseAngle + (i - NUM_BULLETS / 2) * ANGLE_STEP;
            float angleRad = angleDeg * static_cast<float>(MY_PI) / 180.0f;

            Unit::Vec2D dir(std::cos(angleRad), std::sin(angleRad));
            Unit::Vec2D velocity = dir * speed;

            auto bullet = std::make_unique<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
                pos + dir * SPAWN_RADIUS,
                velocity,
                speed,
                1e9
            );
            bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(Unit::Vec2D(0, 0), RADIUS));
            bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(Unit::Vec2D(0, 0), RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0.0f, STARTUP / 2);

            player->spawnBullet(std::move(bullet));
        }
    }
}
