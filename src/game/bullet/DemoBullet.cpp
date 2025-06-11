#include "DemoBullet.hpp"
#include "../hitbox/CircleHitbox.hpp"

#include <cmath>
#include <raylib.h>

DemoBullet::DemoBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction, float radius, float speed, float lifetime)
    : Bullet(ownerId), position(spawnPos), remainingLife(lifetime)
{
    velocity = speed * direction.normalized();
    damagingHitbox = std::make_unique<CircleHitbox>(spawnPos, radius);
    lifeHitbox     = std::make_unique<CircleHitbox>(spawnPos, radius);
}

void DemoBullet::update(float dt) {
    if (isDone()) return;

    remainingLife -= dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (damagingHitbox) damagingHitbox->setPosition(position);
    if (lifeHitbox) lifeHitbox->setPosition(position);
}

bool DemoBullet::isDone() const {
    return remainingLife <= 0.0f;
}
