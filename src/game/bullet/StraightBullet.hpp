#ifndef COMMON_BULLET_HPP
#define COMMON_BULLET_HPP

#include "Bullet.hpp"
#include "CommonBulletGraphicsComponent.hpp"

#include <memory>

/*
    Use this only if you do find yourself needing a bullet with the following properties:
    + Bullet is straight, with a constant speed.
    + Bullet are deleted after a certain time or after going out of bounds.
    + Bullet has life during startup, so bullet can be erased.
    + Bullet has a radius, from which both hitbox (damaging and life) use.
    + This use CommonBulletGraphicsComponent for graphics (or none at all, in which case it uses raylib circle, but that's for demo)
*/

class StraightBullet final : public Bullet {
public:
    StraightBullet(int ownerId, Unit::Vec2D spawnPos, Unit::Vec2D direction,
                   float radius, float speed, float startup, float lifetime, std::unique_ptr<CommonBulletGraphicsComponent> graphics = nullptr);

    void update(float dt) override;
    bool isDone() const override;

    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getVelocity() const override;

private:
    Unit::Vec2D pos;
    Unit::Vec2D vel;
    float radius;

    float remainingTime;
    float remainingStartup;
    bool startedUp = false;

    std::unique_ptr<CommonBulletGraphicsComponent> graphics;
};

#endif // COMMON_BULLET_HPP