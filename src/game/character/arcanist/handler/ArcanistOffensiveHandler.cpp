#include "ArcanistOffensiveHandler.hpp"
#include "../ArcanistGraphicsComponent.hpp"

#include "../../../player/Player.hpp"
#include "../extra/DeathToll.hpp"

#include "../../../../audio/AudioManager.hpp"

ArcanistOffensiveHandler::ArcanistOffensiveHandler(ArcanistGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Offensive), graphics(graphics) {}

void ArcanistOffensiveHandler::tap(bool /*isFocusing*/) {
    graphics->useOffensive();
    AudioManager::getInstance().playSound("ArcanistOffensive1");

    player->spawnBullet(std::make_shared<DeathToll>(player));

    player->applyImplicitMoveLock();
    player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::BasicLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::WideLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, ACTION_LOCK);
}