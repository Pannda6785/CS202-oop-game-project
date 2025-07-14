#include "TapHandler.hpp"

#include "../player/InputBufferer.hpp"
#include "../player/Player.hpp"

TapHandler::TapHandler(Unit::Move move)
    : move(move) {}

bool TapHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("TapHandler::tryRegister - TapHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(Unit::moveToLock(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) return false;

    if (input->tryRegister(Unit::moveToInput(move))) {
        tap(input->isHoldingKey(Unit::Input::Focus));
        return true;
    }

    return false;
}
