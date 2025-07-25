#include "WyrmWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

#include <cmath>

WyrmWideHandler::WyrmWideHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void WyrmWideHandler::update(float dt, const InputBufferer* input) {
    // No combo logic, can be empty or used for cooldowns if needed
}

void WyrmWideHandler::tap(bool isFocusing) {
    // animation

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK_DURATION);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);
}

void WyrmWideHandler::spawnBullet() {
    constexpr float PI = 3.14159265358979323846f;

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D target = player->getTargetPosition();
    Unit::Vec2D aimDir = (target - pos).normalized();

    constexpr float ANGLE_STEP = 360.0f / NUM_BULLETS;
    float baseAngle = std::atan2(aimDir.y, aimDir.x) * 180.0f / static_cast<float>(PI) + ANGLE_STEP / 2;

    std::string bulletTexture = "../assets/sprites/wyrm/bullet/nidhogg_bullet_0_p1_0001.png";
    constexpr float visibleRatio = 0.5f;
    constexpr float textureWidth = 256;
    constexpr float resize = (RADIUS * 2) / (textureWidth * visibleRatio);

    for (int wave = 0; wave < 2; ++wave) {
        float speed = (wave == 0) ? SPEED_IN : SPEED_OUT;

        for (int i = 0; i < NUM_BULLETS; ++i) {
            float angleDeg = baseAngle + (i - NUM_BULLETS / 2) * ANGLE_STEP;
            float angleRad = angleDeg * static_cast<float>(PI) / 180.0f;

            Unit::Vec2D dir(std::cos(angleRad), std::sin(angleRad));
            Unit::Vec2D velocity = dir * speed;

            auto gfx = std::make_unique<CommonBulletGraphicsComponent>(
                bulletTexture,
                resize,
                STARTUP
            );

            auto bullet = std::make_unique<StraightBullet>(
                player->getPlayerId(),
                pos + dir * SPAWN_RADIUS,
                velocity,
                RADIUS,
                speed,
                STARTUP,
                1000,
                std::move(gfx)
            );

            player->spawnBullet(std::move(bullet));
        }
    }
}
