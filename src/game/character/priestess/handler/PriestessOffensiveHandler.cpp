#include "PriestessOffensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"
#include "../../bullet/StraightBullet.hpp"

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

void PriestessOffensiveHandler::onCastRelease() {
    graphics->stopCasting();
    graphics->spin();
    ring->onCastRelease();

    // spawn bullet here, no need cutoff

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
    return 150 + std::min(MAX_CASTING_TIME, castingTime) * RING_SPEED;
}