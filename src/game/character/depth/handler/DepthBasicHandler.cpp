#include "DepthBasicHandler.hpp"
#include "../extra/Whirlpool.hpp"
#include "../../../player/Player.hpp"
#include "../DepthGraphicsComponent.hpp"
#include "../../../../audio/AudioManager.hpp"

DepthBasicHandler::DepthBasicHandler(DepthGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void DepthBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();
    AudioManager::getInstance().playSound("DepthBasic1");

    if (auto whirlpoolPtr = whirlpoolRef.lock()) {
        whirlpoolPtr->detonate();
        whirlpoolRef.reset();
    }

    auto whirlpool = std::make_shared<Whirlpool>(player);
    whirlpoolRef = whirlpool;
    player->spawnBullet(std::move(whirlpool));

    player->applyImplicitMoveLock();
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_VALUE);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
}