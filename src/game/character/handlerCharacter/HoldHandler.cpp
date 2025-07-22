#include "HoldHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/Player.hpp"
#include "HandlerCharacter.hpp"

HoldHandler::HoldHandler(Unit::Move move, float minHoldingTime)
    : move(move), minHoldingTime(minHoldingTime) {}

bool HoldHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("HoldHandler::tryRegister - HoldHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(Unit::moveToLock(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) {
        if (isHolding) { // a disruption! (stun, hit, etc.)
            onHoldRelease(true);
            isHolding = false;
            character->neutralize();
        }
        return false;
    }

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

void HoldHandler::update(float dt, const InputBufferer* input) {
    if (isHolding) {
        holdingTime += dt;
    }
}
