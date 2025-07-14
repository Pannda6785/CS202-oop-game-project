#include "StraightBullet.hpp"

#include "../hitbox/CircleHitbox.hpp"

StraightBullet::StraightBullet(int ownerId, Unit::Vec2D spawnPos, Unit::Vec2D direction,
                                 float radius, float speed, float startup, float lifetime,
                                 std::unique_ptr<CommonBulletGraphicsComponent> graphics)
    : Bullet(ownerId), pos(spawnPos), vel(direction.normalized() * speed), remainingTime(lifetime), remainingStartup(startup),
      startedUp(false), radius(radius), graphics(std::move(graphics))
{
    this->graphics->registerOwner(this);
    lifeHitbox = std::make_unique<CircleHitbox>(pos, radius);
}

void StraightBullet::update(float dt) {
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
    graphics->update(dt);
}

bool StraightBullet::isDone() const {
    if (remainingTime <= 0.0f) return true;
    float margin = 2 * radius * size;
    if (pos.x < -margin || pos.x > Unit::BATTLEFIELD_WIDTH + margin ||
        pos.y < -margin || pos.y > Unit::BATTLEFIELD_HEIGHT + margin) {
        return true;
    }
    return false;
}

Unit::Vec2D StraightBullet::getPosition() const {
    return pos;
}

Unit::Vec2D StraightBullet::getVelocity() const {
    return vel;
}