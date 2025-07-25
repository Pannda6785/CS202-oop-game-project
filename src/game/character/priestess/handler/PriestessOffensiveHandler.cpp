#include "PriestessOffensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"
#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

constexpr float PI = 3.14159265358979323846f;

PriestessOffensiveHandler::PriestessOffensiveHandler(PriestessGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Offensive, MIN_CASTING_TIME), graphics(graphics) {
    ring = std::make_unique<RingGraphicsComponent>(false); // isWide = false
}

void PriestessOffensiveHandler::update(float dt, const InputBufferer* input) {
    CastHandler::update(dt, input);
    ring->update(dt);
    if (cooldownHold > Unit::EPS) {
        cooldownHold -= dt;
        if (cooldownHold < Unit::EPS) {
            cooldownHold = 0.0f;
            player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
        }
    }
    if (isCasting) {
        player->applyModifier(Unit::Modifier::MovementModifier, 1e9, MOVEMENT_MODIFIER_AMOUNT, true);
        if (castingTime > MIN_CASTING_TIME) {
            ring->setVisible(true);
        }
        ring->setRadius(getRingRadius());
        ring->setCenter(player->getPosition());
    }
}

void PriestessOffensiveHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Offensive) {
        if (cooldownHold > Unit::EPS) {
            cooldownHold = 0.0f;
            player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
        }
    }
}

void PriestessOffensiveHandler::onCastStart() {
    graphics->startCasting();
    ring->onCastStart();
}

void PriestessOffensiveHandler::onCastRelease(bool isInterupted) {
    graphics->stopCasting();
    ring->onCastRelease();
    
    if (isInterupted) return;
    
    graphics->spin();
    spawnBullet();

    float lockDuration = std::max(MIN_ACTION_LOCK, MAX_ACTION_LOCK - castingTime);
    player->applyLock(Unit::Lock::BasicLock, lockDuration);
    player->applyLock(Unit::Lock::WideLock, lockDuration);
    player->applyLock(Unit::Lock::OffensiveLock, lockDuration);
    player->applyImplicitMoveLock();

    if (castingTime < CUTOFF) {
        cooldownHold = 0;
        player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
        player->applyModifier(Unit::Modifier::MovementModifier, POST_MOVEMENT_MODIFIER_DURATION, SHORT_POST_MOVEMENT_MODIFIER_AMOUNT, true);
    } else {
        cooldownHold = COOLDOWN;
        player->applyModifier(Unit::Modifier::MovementModifier, POST_MOVEMENT_MODIFIER_DURATION, LONG_POST_MOVEMENT_MODIFIER_AMOUNT, true);
    }
}

float PriestessOffensiveHandler::getRingRadius() const {
    return ADDED_RING_RADIUS + std::min(MAX_CASTING_TIME, castingTime) * RING_SPEED;
}

void PriestessOffensiveHandler::spawnBullet() {
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
    float baseAngleDeg = std::atan2(toTarget.y, toTarget.x) * 180.0f / PI;

    for (int i = 0; i < numBullets; ++i) {
        float angleDeg = baseAngleDeg + (i + 0.5) * angleStep;
        float angleRad = angleDeg * PI / 180.0f;

        Unit::Vec2D direction(std::cos(angleRad), std::sin(angleRad));
        Unit::Vec2D bulletPosition = center + direction * radius;
        
        std::string active = "../assets/sprites/priestess/bullet/priest_bullets_0_p1_0000.png";
        std::string inactive = "../assets/sprites/priestess/bullet/priest_bullets_5_p1_0000.png";
        constexpr float resize = 0.5;

        for (int t = 0; t < 2; ++t) {
            Unit::Vec2D velocity = direction.normalized() * BULLET_SPEED;
            float x = velocity.x;
            float y = velocity.y;
            if (t == 0) {
                velocity = {y, -x};
            } else {
                velocity = {-y, x};
            }
            auto bullet = std::make_unique<StraightBullet>(
                player->getPlayerId(),
                bulletPosition,
                velocity,
                BULLET_RADIUS,
                BULLET_SPEED,
                STARTUP,
                1e9
            );
            auto graphics = std::make_unique<CommonBulletGraphicsComponent>(
                bullet.get(),
                active,
                resize,
                STARTUP / 2,
                true,
                inactive,
                resize
            );
            bullet->addBulletGraphics(std::move(graphics));

            player->spawnBullet(std::move(bullet));
        }
    }
}
