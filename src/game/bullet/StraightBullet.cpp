#include "StraightBullet.hpp"

#include "../hitbox/CircleHitbox.hpp"

StraightBullet::StraightBullet(int ownerId, Unit::Vec2D spawnPos, Unit::Vec2D direction,
                                 float radius, float speed, float startup, float lifetime)
    : Bullet(ownerId), pos(spawnPos), vel(direction.normalized() * speed), remainingTime(lifetime), remainingStartup(startup),
      startedUp(false), radius(radius)
{
    lifeHitbox = std::make_unique<CircleHitbox>(pos, radius * getSize());
}

void StraightBullet::addBulletGraphics(std::unique_ptr<BulletGraphicsComponent> g) {
    graphics = std::move(g);
}

void StraightBullet::update(float dt) {
    if (isDone()) return;
    remainingTime -= dt;
    remainingStartup -= dt;
    if (remainingStartup < 0.0f && !startedUp) {
        startedUp = true;
        damagingHitbox = std::make_unique<CircleHitbox>(pos, radius * getSize());
    }
    pos += vel * dt;
    lifeHitbox->setPosition(pos);
    if (damagingHitbox) {
        damagingHitbox->setPosition(pos);
    }
    if (graphics) graphics->update(dt);
}
bool StraightBullet::isDone() const {
    if (remainingTime <= 0.0f) return true;

    float margin = 4 * radius * getSize();

    // check within battlefield bounds
    float minX = -margin;
    float maxX = Unit::BATTLEFIELD_WIDTH + margin;
    float minY = -margin;
    float maxY = Unit::BATTLEFIELD_HEIGHT + margin;
    if (pos.x >= minX && pos.x <= maxX &&
        pos.y >= minY && pos.y <= maxY) {
        return false;
    }

    // check if can ever re-enter
    bool movingAwayX = (pos.x < minX && vel.x <= Unit::EPS) || (pos.x > maxX && vel.x >= Unit::EPS);
    bool movingAwayY = (pos.y < minY && vel.y <= Unit::EPS) || (pos.y > maxY && vel.y >= Unit::EPS);
    if (movingAwayX || movingAwayY) return true;
    return false;
}


Unit::Vec2D StraightBullet::getPosition() const {
    return pos;
}

Unit::Vec2D StraightBullet::getVelocity() const {
    return vel;
}