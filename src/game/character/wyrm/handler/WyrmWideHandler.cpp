#include "WyrmWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <cmath>

WyrmWideHandler::WyrmWideHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void WyrmWideHandler::tap(bool isFocusing) {
    graphics->roar(MOVEMENT_LOCK_DURATION, 0.25f);

    spawnBullet();

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK_DURATION);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
}

void WyrmWideHandler::spawnBullet() {
    constexpr float MY_PI = 3.14159265358979323846f;

    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D target = player->getTargetPosition();
    Unit::Vec2D aimDir = (target - pos).normalized();

    constexpr float ANGLE_STEP = 360.0f / NUM_BULLETS;
    float baseAngle = std::atan2(aimDir.y, aimDir.x) * 180.0f / static_cast<float>(MY_PI) + ANGLE_STEP / 2;

    auto bulletTexture = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/nidhogg_bullet_0_p1_0001.png");
    constexpr float visibleRatio = 0.5f;
    const float resize = (RADIUS * 2) / (bulletTexture->width * visibleRatio);

    for (int wave = 0; wave < 2; ++wave) {
        float speed = (wave == 0) ? SPEED_IN : SPEED_OUT;

        for (int i = 0; i < NUM_BULLETS; ++i) {
            float angleDeg = baseAngle + (i - NUM_BULLETS / 2) * ANGLE_STEP;
            float angleRad = angleDeg * static_cast<float>(MY_PI) / 180.0f;

            Unit::Vec2D dir(std::cos(angleRad), std::sin(angleRad));

            auto bullet = std::make_shared<StraightBullet>(
                player->getPlayerId(),
                std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
                pos + dir * SPAWN_RADIUS,
                dir,
                speed,
                1e9
            );
            bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
            bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(bullet->getPosition(), RADIUS));
            dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0, STARTUP);

            player->spawnBullet(std::move(bullet));
        }
    }
}
