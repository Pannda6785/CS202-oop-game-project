#include "WyrmDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../WyrmGraphicsComponent.hpp"

#include "../../../bullet/StraightBulletPro.hpp"
#include "../bullet/NoviFireGraphicsComponent.hpp"

WyrmDefensiveHandler::WyrmDefensiveHandler(WyrmGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void WyrmDefensiveHandler::tap(bool isFocusing) {

    player->applyInvincibility(INVINCIBILITY_DURATION, true);

    std::unique_ptr<StraightBulletPro> bullet = std::make_unique<StraightBulletPro>(
        player->getPlayerId(), player->getPosition(), Unit::Vec2D(0, 0), [](float t) -> float { return 0; }, LIFETIME + BLOOM_TIME);
    bullet->addDamagingHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS));
    bullet->removeDamagingHitbox(LIFETIME);
    bullet->addBulletGraphics(std::make_unique<NoviFireGraphicsComponent>(bullet.get(), RADIUS, STARTUP, BLOOM_TIME, LIFETIME));

    player->spawnBullet(std::move(bullet));

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::ArrowLock, ARROW_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyLock(Unit::Lock::BasicLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::WideLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, ACTION_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, ACTION_LOCK);
}
