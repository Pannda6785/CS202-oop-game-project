#include "NoviDispel.hpp"

#include "../../../hitbox/CircleHitbox.hpp"

NoviDispel::NoviDispel(int id, Unit::Vec2D pos)
    : Bullet(id), timeLeft(ACTIVE_TIME) {
    cleansingHitbox = std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize());
    invincibilityHitboxes.emplace_back(std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize()), true, id, INVINCIBILITY_DURATION); 
    invincibilityHitboxes.emplace_back(std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize()), false, id ^ 1, INVINCIBILITY_DURATION);
    modifierHitboxes.emplace_back(std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize()), Unit::Modifier::MovementModifier,
                                  id ^ 1, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    graphics = std::make_unique<NoviDispelGraphicsComponent>(this);
}

void NoviDispel::update(float dt) {
    timeLeft -= dt;
    if (graphics) graphics->update(dt);
    frame++;
    if (frame == 2) modifierHitboxes.clear();
}

bool NoviDispel::isDone() const {
    return timeLeft <= 0.0f;
}