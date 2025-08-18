#include "WyrmOffensiveHandler.hpp"
#include "../WyrmGraphicsComponent.hpp"
#include "../../../player/Player.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"

#include "../../handlerCharacter/HandlerCharacter.hpp"
#include "WyrmBasicHandler.hpp"
#include "WyrmWideHandler.hpp"
#include "WyrmDefensiveHandler.hpp"
#include "DreadwyrmBasicHandler.hpp"
#include "DreadwyrmWideHandler.hpp"
#include "DreadwyrmDefensiveHandler.hpp"
#include "../../../../audio/AudioManager.hpp"

#include <algorithm>

WyrmOffensiveHandler::WyrmOffensiveHandler(WyrmGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Offensive, MIN_CASTING_TIME, MAX_CASTING_TIME), graphics(graphics) {}

void WyrmOffensiveHandler::update(float dt, const InputBufferer* input) {
    if (!bulletRef.lock()) recreateBullet();
    bulletRef.lock()->setPosition(player->getPosition());
    bulletTime += dt;

    CastHandler::update(dt, input);

    if (isActive) timer += dt;

    // check detransform
    if (isActive && timer >= duration) {
        isActive = false;
        detransform();
    }

    // apply active effects
    if (isActive) {
        if (timer >= MOVEMENT_MODIFIER_DURATION_BURST) {
            auto [curDuration, curValue] = player->getModifier(Unit::Modifier::MovementModifier);
            if (movement_modifier < curValue) { // only pull down, so it doesn't clear debuffs
                player->applyModifier(Unit::Modifier::MovementModifier, 0.05f, movement_modifier);
            }
        }
    }

    // apply casting effects
    if (isCasting) {
        player->applyLock(Unit::Lock::MovementLock, 0.05f);
        float sizeUp;
        if (castingTime < MIN_CASTING_TIME) {
            sizeUp = 1 + (castingTime / MIN_CASTING_TIME) * (MIN_SIZEUP - 1);
        } else {
            sizeUp = MIN_SIZEUP + getRatio() * (MAX_SIZEUP - MIN_SIZEUP);
        }
        player->applyModifier(Unit::Modifier::SizeModifier, 0.05f, sizeUp);

        chargeGraphicsRef->setRadius(getRadius());
    }
}

void WyrmOffensiveHandler::onCastStart() {
    if (!bulletRef.lock()) recreateBullet();
    graphics->roar(1e9, 0);
    AudioManager::getInstance().playSound("WyrmChargeTransform");
    isActive = false;
    chargeGraphicsRef->reset();
    chargeGraphicsRef->setVisible(true);
}

void WyrmOffensiveHandler::onCastRelease(bool isInterupted) {
    if (!bulletRef.lock()) recreateBullet();
    if (isInterupted) {
        return;
    }
    isActive = true;
    timer = 0.0f;

    transform();

    bulletRef.lock()->addCleansingHitbox(castingTime, std::make_unique<CircleHitbox>(player->getPosition(), getRadius()));
    bulletRef.lock()->removeCleansingHitbox(castingTime + 0.02f);

    duration = MIN_DURATION + (MAX_DURATION - MIN_DURATION) * getRatio();
    movement_modifier = MOVEMENT_MODIFIER_VALUE_GREATEST + (MOVEMENT_MODIFIER_VALUE_LEAST - MOVEMENT_MODIFIER_VALUE_GREATEST) * (1 - getRatio());
    
    float sizeUp = MIN_SIZEUP + (MAX_SIZEUP - MIN_SIZEUP) * getRatio();
    float bulletSizeUp = BULLET_MIN_SIZEUP + (BULLET_MAX_SIZEUP - BULLET_MIN_SIZEUP) * getRatio();
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_BURST, MOVEMENT_MODIFIER_VALUE_BURST);
    player->applyModifier(Unit::Modifier::SizeModifier, duration, sizeUp);
    player->applyModifier(Unit::Modifier::BulletSizeModifier, duration, bulletSizeUp);

    player->applyImplicitMoveLock();
    player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
}

float WyrmOffensiveHandler::getRadius() const { // for indicator and bullet hitbox only
    return std::max(MIN_RADIUS, std::min(MAX_RADIUS, MIN_RADIUS + (castingTime / MAX_CASTING_TIME) * (MAX_RADIUS - MIN_RADIUS)));
}

float WyrmOffensiveHandler::getRatio() const {
    float ratio = (castingTime - MIN_CASTING_TIME) / (MAX_CASTING_TIME - MIN_CASTING_TIME);
    ratio *= ratio; // the longer the crazier
    return ratio;
}

void WyrmOffensiveHandler::transform() {
    chargeGraphicsRef->setVisible(false);
    rippleGraphicsRef->reset();
    graphics->roar(0.01f, 0.2f);
    graphics->transform();
    AudioManager::getInstance().playSound("WyrmTransform");
    character->setHandler(Unit::Move::Basic, std::make_unique<DreadwyrmBasicHandler>(graphics));
    character->setHandler(Unit::Move::Wide, std::make_unique<DreadwyrmWideHandler>(graphics));
    character->setHandler(Unit::Move::Defensive, std::make_unique<DreadwyrmDefensiveHandler>(graphics));
}

void WyrmOffensiveHandler::detransform() {
    rippleGraphicsRef->reset();
    graphics->detransform();
    AudioManager::getInstance().playSound("WyrmDetransform");
    character->setHandler(Unit::Move::Basic, std::make_unique<WyrmBasicHandler>(graphics));
    character->setHandler(Unit::Move::Wide, std::make_unique<WyrmWideHandler>(graphics));
    character->setHandler(Unit::Move::Defensive, std::make_unique<WyrmDefensiveHandler>(graphics));
}

void WyrmOffensiveHandler::recreateBullet() {
    if (bulletRef.lock()) {
        std::cerr << "Warning: WyrmOffensiveHandler::recreateBullet - bulletRef is still valid." << std::endl;
        return;
    }
    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        Unit::Vec2D{0, 0},
        Unit::Vec2D{0, 0},
        0,
        1e9f
    );
    bulletRef = bullet;
    
    std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 80;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color);
    chargeGraphicsRef = chargeGraphics.get();
    chargeGraphics->addInner(std::array<int, 4>{255, 255, 255, 100}, MIN_RADIUS / 0.3f, true);
    chargeGraphics->setVisible(false);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics), 0, 1e9, true);

    std::array<int, 4> purple = {118, 11, 186, 240};
    auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(purple, 2, 0, MAX_RADIUS, 0.3f, 0.4f, 9);
    rippleGraphicsRef = rippleGraphics.get();
    rippleGraphics->setVisible(false);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(rippleGraphics), 0, 1e9, true);
        
    player->spawnBullet(std::move(bullet));
    bulletTime = 0.0f;
}