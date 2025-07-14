#include "PriestessDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

PriestessDefensiveHandler::PriestessDefensiveHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void PriestessDefensiveHandler::tap(bool isFocusing) {
    graphics->yell(0.8f);
    player->applyInvincibility(3.0f);

    player->applyImplicitMoveLock();
    player->applyCooldown(move, 15.0f);
    player->applyLock(Unit::Lock::MovementLock, 0.5f);
}
