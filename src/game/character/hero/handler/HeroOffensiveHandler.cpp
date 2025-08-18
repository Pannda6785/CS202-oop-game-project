#include "HeroOffensiveHandler.hpp"
#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"
#include "../../../../audio/AudioManager.hpp"

HeroOffensiveHandler::HeroOffensiveHandler(HeroGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Offensive), graphics(graphics), timer(1e9) {}

void HeroOffensiveHandler::update(float dt, const InputBufferer* input) {
    timer += dt;
    if (timer - 2 * dt < MOVEMENT_MODIFIER_DURATION_1 && timer >= MOVEMENT_MODIFIER_DURATION_1) {
        player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_2, MOVEMENT_MODIFIER_VALUE_2);
    }
}

void HeroOffensiveHandler::tap(bool isFocusing) {
    timer = 0;
    
    graphics->roll();
    AudioManager::getInstance().playSound("Attack1");
    AudioManager::getInstance().playSound("HeroRoll");

    player->applyInvincibility(INVINCIBILITY_DURATION, false);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION_1, MOVEMENT_MODIFIER_VALUE_1);

    player->applyImplicitMoveLock();
    player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
    player->applyLock(Unit::Lock::BasicLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::WideLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, ACTION_LOCK);
}
