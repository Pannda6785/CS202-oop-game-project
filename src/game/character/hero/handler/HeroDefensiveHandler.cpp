#include "HeroDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"

#include "../../../bullet/StraightBullet.hpp"
#include "../../../bullet/CompositeBulletGraphicsComponent.hpp"
#include "../../../bullet/effect/RippleGraphicsComponent.hpp"
#include "../../../bullet/effect/ChargeGraphicsComponent.hpp"
#include "../extra/StunGraphicsComponent.hpp"

HeroDefensiveHandler::HeroDefensiveHandler(HeroGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void HeroDefensiveHandler::tap(bool isFocusing) {
    graphics->stun();

    player->applyInvincibility(INVINCIBILITY_DURATION, false);
    spawnBullet();

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
    player->applyLock(Unit::Lock::BasicLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::WideLock, ATTACK_LOCK);
    player->applyLock(Unit::Lock::OffensiveLock, SPELL_LOCK);
    player->applyLock(Unit::Lock::DefensiveLock, SPELL_LOCK);
}

void HeroDefensiveHandler::spawnBullet() {
    auto bullet = std::make_shared<StraightBullet>(
        player->getPlayerId(),
        std::make_unique<CompositeBulletGraphicsComponent>(),
        player->getPosition(),
        Unit::Vec2D{0, 0},
        0,
        LIFETIME
    );

    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::MovementLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::ArrowLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::BasicLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::WideLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::OffensiveLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addLockHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), RADIUS), Unit::Lock::DefensiveLock, player->getPlayerId() ^ 1, STUN_DURATION);
    bullet->addCleansingHitbox(STARTUP, std::make_unique<CircleHitbox>(player->getPosition(), CLEANSE_RADIUS));

    bullet->removeCleansingHitbox(STARTUP + 0.02f);
    bullet->removeLockHitboxes(STARTUP + 0.02f);

    std::array<int, 4> color = graphics->getSignatureColor(); color[3] = 170;
    std::array<int, 4> lighter;
    const int T = 8;
    for (int i = 0; i < 4; i++) lighter[i] = (color[i] + (T - 1) * 255) / T;
    lighter[3] = 200;
    auto chargeGraphics = std::make_unique<ChargeGraphicsComponent>(color, RADIUS, RADIUS, STARTUP - 0.03);
    chargeGraphics->addInner(lighter, RADIUS / STARTUP, false);
    lighter[3] = 240;
    auto rippleGraphics = std::make_unique<RippleGraphicsComponent>(lighter, 2, 0, RADIUS, 0.3f, 0.4f, 6);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(chargeGraphics), 0.0f, STARTUP - 0.03f);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::move(rippleGraphics), STARTUP, LIFETIME);
    dynamic_cast<CompositeBulletGraphicsComponent*>(bullet->getGraphics())->addComponent(std::make_unique<StunGraphicsComponent>(color, player->getWorld()), STARTUP - 0.03, LIFETIME);

    player->spawnBullet(std::move(bullet));
}