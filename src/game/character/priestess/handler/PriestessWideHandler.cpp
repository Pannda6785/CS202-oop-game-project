#include "PriestessWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/TextureBulletGraphicsComponent.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include "../../../../audio/AudioManager.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

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

void PriestessWideHandler::onCastRelease(bool isInterupted) {
    graphics->stopCasting();
    ring->onCastRelease();
    
    if (isInterupted) return;

    graphics->yell();
    AudioManager::getInstance().playSound("Attack5");
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
    constexpr float MY_PI = 3.14159265358979323846f;

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
    float baseAngleDeg = std::atan2(toTarget.y, toTarget.x) * 180.0f / MY_PI;

    auto activeTexture = TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_2_p1_1.png");
    auto inactiveTexture = TextureManager::instance().getTexture("../assets/sprites/priestess/bullet/spr_prs_2_p1_0.png");
    constexpr float visibleRatio = 3.5f / 6.0f;
    float resize = (BULLET_RADIUS * 2) / (activeTexture->width * visibleRatio);

    for (int i = 0; i < numBullets; ++i) {
        float angleDeg = baseAngleDeg + (i + 0.5) * angleStep;
        float angleRad = angleDeg * MY_PI / 180.0f;

        Unit::Vec2D direction(std::cos(angleRad), std::sin(angleRad));
        Unit::Vec2D bulletPosition = center + direction * radius;

        float startup = (castingTime < CUTOFF) ? SHORT_STARTUP : LONG_STARTUP;

        auto bullet = std::make_shared<StraightBullet>(
            player->getPlayerId(),
            std::make_unique<TextureBulletGraphicsComponent>(activeTexture, resize),
            bulletPosition,
            direction,
            BULLET_SPEED,
            1e9
        );
        bullet->addLifeHitbox(0.0f, std::make_unique<CircleHitbox>(bullet->getPosition(), BULLET_RADIUS));
        bullet->addDamagingHitbox(startup, std::make_unique<CircleHitbox>(bullet->getPosition(), BULLET_RADIUS));
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addBloom(-startup / 6, startup / 3);
        dynamic_cast<TextureBulletGraphicsComponent*>(bullet->getGraphics())->addStartup(inactiveTexture, resize);

        player->spawnBullet(std::move(bullet));
    }
}
