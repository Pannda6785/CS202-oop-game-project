#include "DreadwyrmBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../extra/DreadFire.hpp"

#include <cmath>

DreadwyrmBasicHandler::DreadwyrmBasicHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void DreadwyrmBasicHandler::tap(bool isFocusing) {
    graphics->blast(0.050f, 0.250f);

    player->spawnBullet(std::make_shared<DreadFire>(
        player,
        player->getBulletSpawner()
    ));

    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);
    player->applyLock(Unit::Lock::BasicLock, BASIC_LOCK);
    player->applyLock(Unit::Lock::WideLock, WIDE_LOCK);
}
