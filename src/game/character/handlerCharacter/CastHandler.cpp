#include "CastHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/Player.hpp"
#include "HandlerCharacter.hpp"

CastHandler::CastHandler(Unit::Move move, float minCastingTime)
    : move(move), minCastingTime(minCastingTime) {}

bool CastHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("CastHandler::tryRegister - CastHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(Unit::moveToLock(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) return false;

    Unit::Input inputKey = Unit::moveToInput(move);
    if (!isCasting) {
        if (input->isHoldingKey(inputKey)) {
            input->tryRegister(inputKey); // Flush earlier inputs
            isCasting = true;
            castingTime = 0.0f;
            character->setOrder({move});
            onCastStart();
            return true;
        } else {
            return false;
        }
    } else {
        if (input->isHoldingKey(inputKey) || castingTime < minCastingTime) { // force hold for minCastingTime
            return true;
        } else {
            onCastRelease();
            isCasting = false;
            character->neutralize();
            return true;
        }
    }
}

void CastHandler::update(float dt, const InputBufferer* input) {
    if (isCasting) {
        castingTime += dt;
    }
}
