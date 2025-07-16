#include "NoviDispel.hpp"

#include "../../../hitbox/CircleHitbox.hpp"

NoviDispel::NoviDispel(int id, Unit::Vec2D pos)
    : Bullet(id), timeLeft(ACTIVE_TIME) {
    cleansingHitbox = std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize());
    invincibilityHitboxes.emplace_back(std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize()), id, INVINCIBILITY_DURATION); 
    invincibilityHitboxes.emplace_back(std::make_unique<CircleHitbox>(pos, BASE_RADIUS * getSize()), id ^ 1, INVINCIBILITY_DURATION); 
    graphics = std::make_unique<NoviDispelGraphicsComponent>(this);
}

void NoviDispel::update(float dt) {
    timeLeft -= dt;
    if (graphics) graphics->update(dt);
}

bool NoviDispel::isDone() const {
    return timeLeft <= 0.0f;
}