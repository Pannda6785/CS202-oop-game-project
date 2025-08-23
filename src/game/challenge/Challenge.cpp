#include "Challenge.hpp"

#include "../World.hpp"
#include "../pattern/Pattern.hpp"

void Challenge::addPattern(World* world, std::unique_ptr<Pattern> pattern, float time) {
    world->addPattern(std::move(pattern), time);
}

void Challenge::applyModifier(World* world, Unit::Modifier mod, float duration, float value) {
    for (auto& playerPtr : world->players) {
        playerPtr->applyModifier(mod, duration, value, true);
    }
}

void Challenge::applyLock(World* world, Unit::Lock lock, float duration) {
    for (auto& playerPtr : world->players) {
        playerPtr->applyLock(lock, duration, true);
    }
}