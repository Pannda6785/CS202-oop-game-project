#include "WyrmOffensiveHandler.hpp"
#include "../WyrmGraphicsComponent.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"

#include <algorithm>

WyrmOffensiveHandler::WyrmOffensiveHandler(WyrmGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Offensive, MIN_CASTING_TIME, MAX_CASTING_TIME), graphics(graphics) {}

void WyrmOffensiveHandler::update(float dt, const InputBufferer* input) {
    CastHandler::update(dt, input);
    
    if (isActive && timer < duration) {
        timer += dt;    
        if (timer >= MOVEMENT_MODIFIER_DURATION_BURST) {
            auto [curDuration, curValue] = player->getModifier(Unit::Modifier::MovementModifier);
            if (MOVEMENT_MODIFIER_VALUE < curValue) { // only pull down, so it doesn't clear debuffs
                player->applyModifier(Unit::Modifier::MovementModifier, 0.05f, MOVEMENT_MODIFIER_VALUE);
            }
        }
    }
    
    if (isCasting) {
        player->applyLock(Unit::Lock::MovementLock, 0.05f);
        float sizeUp;
        if (castingTime < MIN_CASTING_TIME) {
            sizeUp = 1 + (castingTime / MIN_CASTING_TIME) * (MIN_SIZEUP - 1);
        } else {
            sizeUp = MIN_SIZEUP + (castingTime - MIN_CASTING_TIME) / (MAX_CASTING_TIME - MIN_CASTING_TIME) * (MAX_SIZEUP - MIN_SIZEUP);
        }
        player->applyModifier(Unit::Modifier::SizeModifier, 0.05f, sizeUp);

        chargeGraphicsRef->setRadius(getRadius());
    }
}

void WyrmOffensiveHandler::onCastStart() {
    graphics->roar(1e9, 0);
    isActive = false;
    
    auto bullet = std::make_unique<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition(),
        Unit::Vec2D{0, 0},
        0,
        MAX_CASTING_TIME + 0.8f
    );
    bulletRef = bullet.get();
    
    std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 80;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color);
    chargeGraphicsRef = chargeGraphics.get();
    chargeGraphics->addInner(std::array<int, 4>{255, 255, 255, 100}, MIN_RADIUS / 0.3f, true);

    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics), 0.0f, MAX_CASTING_TIME + 0.8f);

    player->spawnBullet(std::move(bullet));
}

void WyrmOffensiveHandler::onCastRelease(bool isInterupted) {
    if (isInterupted) return;
    isActive = true;
    timer = 0.0f;
    graphics->roar(0.01f, 0.2f);

    float ratio = (castingTime - MIN_CASTING_TIME) / (MAX_CASTING_TIME - MIN_CASTING_TIME);
    ratio *= ratio; // the longer the crazier
    duration = MIN_DURATION + (MAX_DURATION - MIN_DURATION) * ratio;
    float sizeUp = MIN_SIZEUP + (MAX_SIZEUP - MIN_SIZEUP) * ratio;
    float bulletSizeUp = BULLET_MIN_SIZEUP + (BULLET_MAX_SIZEUP - BULLET_MIN_SIZEUP) * ratio;

    chargeGraphicsRef->setVisible(false);
    auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(graphics->getSignatureColor(), 2, 0, getRadius(), 0.3f, 0.4f, 6);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bulletRef->getGraphics())->addComponent(std::move(rippleGraphics), castingTime, 1e9);
    bulletRef->addCleansingHitbox(castingTime, std::make_unique<CircleHitbox>(player->getPosition(), getRadius()));
    bulletRef->removeCleansingHitbox(castingTime + 0.02f);

    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_BURST, MOVEMENT_MODIFIER_VALUE_BURST);
    player->applyModifier(Unit::Modifier::SizeModifier, duration, sizeUp);
    player->applyModifier(Unit::Modifier::BulletSizeModifier, duration, bulletSizeUp);

    player->applyImplicitMoveLock();
    player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
}

float WyrmOffensiveHandler::getRadius() const {
    return std::max(MIN_RADIUS, std::min(MAX_RADIUS, MIN_RADIUS + (castingTime / MAX_CASTING_TIME) * (MAX_RADIUS - MIN_RADIUS)));
}