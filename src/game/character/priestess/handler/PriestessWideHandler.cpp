#include "PriestessWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"
#include "../../bullet/StraightBullet.hpp"
#include "../../bullet/CommonBulletGraphicsComponent.hpp"

PriestessWideHandler::PriestessWideHandler(PriestessGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Wide, MIN_CASTING_TIME), graphics(graphics) {
    ring = std::make_unique<RingGraphicsComponent>(true); // isWide = true
}

void PriestessWideHandler::update(float dt, const InputBufferer* input) {
    CastHandler::update(dt, input);
    ring->update(dt);
    if (isCasting) {
        player->applyModifier(Unit::Modifier::MovementModifier, 1e9, MOVEMENT_MODIFIER_AMOUNT, true);
        if (castingTime > MIN_CASTING_TIME) {
            ring->setVisible(true);
        }
        ring->setRadius(getRingRadius());
        ring->setCenter(player->getPosition());
    }
}

void PriestessWideHandler::onCastStart() {
    graphics->startCasting();
    ring->onCastStart();
}

void PriestessWideHandler::onCastRelease() {
    graphics->stopCasting();
    graphics->yell();
    ring->onCastRelease();

    spawnBullet();

    player->applyModifier(Unit::Modifier::MovementModifier, 0.01, 1, true);
    float lockDuration = std::max(MIN_ACTION_LOCK, MAX_ACTION_LOCK - castingTime);
    player->applyLock(Unit::Lock::BasicLock, lockDuration);
    player->applyLock(Unit::Lock::WideLock, lockDuration);
    player->applyLock(Unit::Lock::OffensiveLock, lockDuration);
    player->applyImplicitMoveLock();
}

float PriestessWideHandler::getRingRadius() const {
    return ADDED_RING_RADIUS + std::min(MAX_CASTING_TIME, castingTime) * RING_SPEED;
}

void PriestessWideHandler::spawnBullet() {
    auto getRate = [&](float x) -> float {
        float t = (x - ADDED_RING_RADIUS) / (RING_SPEED - ADDED_RING_RADIUS);
        if (t > 1) t = 1;
        return MAX_NUM_BULLETS_RATIO - DECAY_RATE * t;
    };

    float radius = getRingRadius();
    int numBullets = static_cast<int>(getRate(radius) * radius);
    float angleStep = 360.0f / numBullets;

    Unit::Vec2D center = player->getPosition(); 
    Unit::Vec2D target = player->getTargetPosition();
    Unit::Vec2D toTarget = (target - center).normalized();

    // Compute rotation angle in degrees
    float baseAngleDeg = std::atan2(toTarget.y, toTarget.x) * 180.0f / M_PI;

    for (int i = 0; i < numBullets; ++i) {
        float angleDeg = baseAngleDeg + (i + 0.5) * angleStep;
        float angleRad = angleDeg * M_PI / 180.0f;

        Unit::Vec2D direction(std::cos(angleRad), std::sin(angleRad));
        Unit::Vec2D bulletPosition = center + direction * radius;

        float startup = (castingTime < CUTOFF) ? SHORT_STARTUP : LONG_STARTUP;
        std::string path = "../assets/sprites/priestess/bullet/priest_bullets_4_p1_0001.png";
        constexpr float resize = 0.6364;

        auto graphics = std::make_unique<CommonBulletGraphicsComponent>(
            path,
            resize,
            startup
        );

        auto bullet = std::make_unique<StraightBullet>(
            player->getPlayerId(),
            bulletPosition,
            direction.normalized() * BULLET_SPEED,
            BULLET_RADIUS,
            BULLET_SPEED,
            startup,
            1e9,
            std::move(graphics)
        );

        player->spawnBullet(std::move(bullet));
    }
}
