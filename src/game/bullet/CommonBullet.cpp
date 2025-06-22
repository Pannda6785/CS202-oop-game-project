#include "CommonBullet.hpp"

#include "../hitbox/CircleHitbox.hpp"

CommonBullet::CommonBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction,
                           float radius, float speed, float startup, float lifetime)
    : Bullet(ownerId), pos(spawnPos), vel(direction.normalized() * speed), remainingTime(lifetime), remainingStartup(startup),
      startedUp(false), radius(radius)
{
    lifeHitbox = std::make_unique<CircleHitbox>(pos, radius);
    graphics = std::make_unique<CommonBulletGraphicsComponent>(this);
}

CommonBullet::CommonBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction,
                           float radius, float speed, float startup, float lifetime, const std::string& texturePath)
    : Bullet(ownerId), pos(spawnPos), vel(direction.normalized() * speed), remainingTime(lifetime), remainingStartup(startup), 
      startedUp(false), radius(radius)
{
    lifeHitbox = std::make_unique<CircleHitbox>(pos, radius);
    graphics = std::make_unique<CommonBulletGraphicsComponent>(this, texturePath);
}

CommonBullet::~CommonBullet() {}

void CommonBullet::update(float dt) {
    if (isDone()) return;
    remainingTime -= dt;
    remainingStartup -= dt;
    if (remainingStartup < 0.0f && !startedUp) {
        startedUp = true;
        damagingHitbox = std::make_unique<CircleHitbox>(pos, radius);
    }
    pos += vel * dt;
    lifeHitbox->setPosition(pos);
    if (damagingHitbox) {
        damagingHitbox->setPosition(pos);
    }
}

bool CommonBullet::isDone() const {
    return remainingTime <= 0.0f;
}

const Unit::Vec2D& CommonBullet::getPosition() const {
    return pos;
}

const Unit::Vec2D& CommonBullet::getVelocity() const {
    return vel;
}