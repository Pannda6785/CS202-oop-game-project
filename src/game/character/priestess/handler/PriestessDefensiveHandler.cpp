#include "PriestessDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"
#include "../bullet/NoviDispel.hpp"

PriestessDefensiveHandler::PriestessDefensiveHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void PriestessDefensiveHandler::tap(bool isFocusing) {
    graphics->yell(0.8f);

    player->spawnBullet(std::make_unique<NoviDispel>(player->getPlayerId(), player->getPosition()));

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
}
