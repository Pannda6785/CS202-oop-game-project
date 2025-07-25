#include "WyrmDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"
#include "../bullet/NoviFire.hpp"
#include "../../../bullet/CommonBulletGraphicsComponent.hpp"

WyrmDefensiveHandler::WyrmDefensiveHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void WyrmDefensiveHandler::tap(bool isFocusing) {

    player->applyInvincibility(INVINCIBILITY_DURATION, true);

    player->spawnBullet(std::make_unique<NoviFire>(player->getPlayerId(), player->getPosition()));

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyLock(Unit::Lock::BasicLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::WideLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, ACTION_LOCK);
}
