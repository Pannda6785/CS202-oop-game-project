#include "CastHandler.hpp"

#include "../../player/InputBufferer.hpp"
#include "../../player/Player.hpp"
#include "HandlerCharacter.hpp"

CastHandler::CastHandler(Unit::Move move, float minCastingTime, float maxCastingTime)
    : move(move), minCastingTime(minCastingTime), maxCastingTime(maxCastingTime) {}

bool CastHandler::tryRegister(InputBufferer* input) {
    if (!player || !character) {
        throw std::runtime_error("CastHandler::tryRegister - CastHandler must be registered with a player and character before use.");
    }

    float lock = player->getLock(Unit::moveToLock(move));
    float cooldown = player->getCooldown(move);
    if (lock > Unit::EPS || cooldown > Unit::EPS) {
        if (isCasting) { // a disruption! (stun, hit, etc.)
            onCastRelease(true);
            isCasting = false;
            character->neutralize();
        }
        return false;
    }

    Unit::Input inputKey = Unit::moveToInput(move);
    if (!isCasting) {
        if (input->tryRegister(inputKey)) {
            isCasting = true;
            castingTime = 0.0f;
            character->setOrder({move});
            onCastStart();
            return true;
        } else {
            return false;
        }
    } else {
        if ((castingTime < minCastingTime) || (input->isHoldingKey(inputKey) && castingTime < maxCastingTime)) { 
            // force hold cast for min time or once max time then must release
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
