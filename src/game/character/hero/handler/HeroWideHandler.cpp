#include "HeroWideHandler.hpp"
#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <cmath>

HeroWideHandler::HeroWideHandler(HeroGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics), timer(1e9) {}

void HeroWideHandler::update(float dt, const InputBufferer* input) {
    timer += dt;
    if (timer - 2 * dt < DELAY && timer >= DELAY) {
        // Shoo to the two sides
        for (float sideAngle : {90.0f, -90.0f}) {
            spawnBullet(sideAngle);
        }
    }
}

void HeroWideHandler::tap(bool isFocusing) {
    timer = 0;
    
    graphics->useWide();
    
    // Record the TRUE direction toward enemy
    Unit::Vec2D pos = player->getPosition();
    Unit::Vec2D target = player->getTargetPosition();
    directionSnapshot = (target - pos).normalized();

    // Forward and backward
    spawnBullet(0.0f);
    spawnBullet(180.0f);

    player->applyImplicitMoveLock();
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_VALUE);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
}

void HeroWideHandler::spawnBullet(float angle) {
    constexpr float MY_PI = 3.14159265358979323846f;

    const Texture* bulletTexture = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/spr_fen_0_wh_7_1.png");
    constexpr float visibleRatio = 2.5f / 6.0f;
    const float resize = (RADIUS * 2) / (bulletTexture->width * visibleRatio);

    Unit::Vec2D pos = player->getPosition();
    float baseAngle = std::atan2(directionSnapshot.y, directionSnapshot.x) * 180.0f / static_cast<float>(MY_PI);
    float angleDeg = baseAngle + angle;
    float rad = angleDeg * MY_PI / 180.0f;
    Unit::Vec2D dir(std::cos(rad), std::sin(rad));

    // Offsets for the 4 bullets
    float offsets[4] = {180.0f, 110.0f, -110.0f, -180.0f};
    Unit::Vec2D perp = Unit::Vec2D(-dir.y, dir.x).normalized();

    // Speed function: linear interpolation from SPEED_INIT to SPEED_FINAL over LIFETIME
    auto speedFunc = [](float t) {
        float s = HeroWideHandler::SPEED_INIT + (HeroWideHandler::SPEED_FINAL - HeroWideHandler::SPEED_INIT) * (t / HeroWideHandler::LIFETIME);
        return s;
    };

    for (float offset : offsets) {
        Unit::Vec2D spawnPos = pos + dir * RADIUS + perp * offset;

        auto bullet = std::make_unique<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(bulletTexture, resize),
            spawnPos,
            dir,
            speedFunc,
            LIFETIME + FADEOUT
        );
        bullet->addLifeHitbox(0, std::make_unique<CircleHitbox>(spawnPos, RADIUS));
        bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(spawnPos, RADIUS));
        bullet->removeDamagingHitbox(LIFETIME);
        bullet->removeLifeHitbox(LIFETIME);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadein(0.0f, STARTUP / 2);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addVelocityRotation(true);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addFadeout(LIFETIME, LIFETIME + FADEOUT);

        player->spawnBullet(std::move(bullet));
    }
}