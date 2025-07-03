#include "DefensiveHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/IPlayerControl.hpp"

DefensiveHandler::DefensiveHandler()
    : TapHandler(Unit::Move::Defensive) {}

void DefensiveHandler::tap() {
    player->applyInvincibility(3.0f);
    // TO DO: properly does the right move
    player->applyCooldown(move, 15.0f);
    player->applyLock(Unit::Lock::MovementLock, 0.5f);
    player->applyImplicitMoveLock();
}
