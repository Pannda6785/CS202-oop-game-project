#include "HoldHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/Player.hpp"

HoldHandler::HoldHandler(Unit::Move move)
    : move(move) {}

bool HoldHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("HoldHandler::tryRegister - HoldHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(Unit::moveToLock(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) return false;

    if (input->isHoldingKey(Unit::moveToInput(move))) {
        input->tryRegister(Unit::moveToInput(move)); // flush any previous input
        tick(input->isHoldingKey(Unit::Input::Focus));
        return true;
    }

    return false;
}