#ifndef COMMON_BULLET_HPP
#define COMMON_BULLET_HPP

#include "Bullet.hpp"
#include "CommonBulletGraphicsComponent.hpp"

#include <string>
#include <memory>

/*
    DISCLAIMER: 
    Each move is expected to implement their own bullet class.
    However, that is rarely practical, as many types of bullet are just straght line bullet.
    Use this only if you do find yourself needing a bullet with the following properties:
    + Texture's path must be passed in the constructor.
    + Bullet is straight, with a constant speed.
    + Bullet has a radius, from which both hitbox.
    + Bullet has life during startup, so bullet can be erased.
    + Texture uses hitbox position AND velocity's direction to render.
*/

class CommonBullet : public Bullet {
public:
    CommonBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction,
                 float radius, float speed, float startup, float lifetime);

    CommonBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction,
                 float radius, float speed, float startup, float lifetime, const std::string& texturePath);

    ~CommonBullet();

    void update(float dt) override;
    bool isDone() const override;

    const Unit::Vec2D& getPosition() const;
    const Unit::Vec2D& getVelocity() const;

private:
    Unit::Vec2D pos;
    Unit::Vec2D vel;
    float remainingTime;
    float remainingStartup;
    bool startedUp = false;
    float radius;

    std::unique_ptr<CommonBulletGraphicsComponent> graphics;
};

#endif // COMMON_BULLET_HPP