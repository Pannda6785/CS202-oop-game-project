#include "PriestessDefensiveHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

#include "../../../bullet/StraightBulletPro.hpp"
#include "../bullet/NoviDispelGraphicsComponent.hpp"

PriestessDefensiveHandler::PriestessDefensiveHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Defensive), graphics(graphics) {}

void PriestessDefensiveHandler::tap(bool isFocusing) {
    graphics->yell(0.8f);

    std::unique_ptr<StraightBulletPro> bullet = std::make_unique<StraightBulletPro>(
        player->getPlayerId(), player->getPosition(), Unit::Vec2D(0, 0), [](float t) -> float { return 0; }, LIFETIME);

    bullet->addBulletGraphics(std::make_unique<NoviDispelGraphicsComponent>(bullet.get()));

    bullet->addInvincibilityHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), true, 
                                    player->getPlayerId(), INVINCIBILITY_DURATION);
    bullet->addInvincibilityHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), false, 
                                    player->getPlayerId() ^ 1, INVINCIBILITY_DURATION);
    bullet->addCleansingHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), CLEANSE_RADIUS));

    bullet->addModifierHitbox(0.0f, std::make_unique<CircleHitbox>(player->getPosition(), BASE_RADIUS), Unit::Modifier::MovementModifier,
                                    player->getPlayerId() ^ 1, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    bullet->removeModifierHitboxes(0.1f);

    player->spawnBullet(std::move(bullet));

    player->applyImplicitMoveLock(true);
    player->applyCooldown(move, COOLDOWN);
    player->applyLock(Unit::Lock::MovementLock, MOVEMENT_LOCK);
}
