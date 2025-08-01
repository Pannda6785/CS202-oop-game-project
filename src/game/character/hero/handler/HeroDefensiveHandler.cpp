#include "HeroDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"

#include "../../../bullet/StraightBulletPro.hpp"
#include "../bullet/StunWaveGraphicsComponent.hpp"

HeroDefensiveHandler::HeroDefensiveHandler(HeroGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void HeroDefensiveHandler::tap(bool isFocusing) {
    graphics->stun();

    player->applyInvincibility(INVINCIBILITY_DURATION, false);

    std::unique_ptr<StraightBulletPro> bullet = std::make_unique<StraightBulletPro>(
        player->getPlayerId(), player->getPosition(), Unit::Vec2D(0, 0), [](float t) -> float { return 0; }, LIFETIME + BLOOM_TIME);
    
    bullet->addBulletGraphics(std::make_unique<StunWaveGraphicsComponent>(bullet.get(), RADIUS, STARTUP, BLOOM_TIME, LIFETIME));
    
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::MovementLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::ArrowLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::BasicLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::WideLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::OffensiveLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::DefensiveLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addCleansingHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS));

    bullet->removeCleansingHitbox(STARTUP + 0.02f);
    bullet->removeLockHitboxes(STARTUP + 0.02f);

    player->spawnBullet(std::move(bullet));

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
}