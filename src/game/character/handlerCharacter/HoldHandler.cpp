#include "HoldHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/IPlayerControl.hpp"
#include "HandlerCharacter.hpp"

HoldHandler::HoldHandler(Unit::Move move, float minHoldingTime)
    : move(move), minHoldingTime(minHoldingTime) {}

bool HoldHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("HoldHandler::tryRegister - HoldHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(static_cast<Unit::Lock>(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) return false;

    Unit::Input inputKey = Unit::moveToInput(move);

    if (!isHolding) {
        if (input->isHoldingKey(inputKey)) {
            input->tryRegister(inputKey); // flush any previous input
            isHolding = true;
            holdingTime = 0.0f;
            onHoldStart();
            return true;
        } else {
            return false;
        }
    } else {
        if (input->isHoldingKey(inputKey)) {
            return true;
        } else {
            onHoldRelease();
            isHolding = false;
            return true;
        }
    }
}

void HoldHandler::update(float dt) {
    if (isHolding) {
        holdingTime += dt;
    }
}
